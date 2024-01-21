/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:35:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:36:16 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	count_processes(t_process *process)
{
	int	num_processes;

	num_processes = 0;
	while (process != NULL)
	{
		num_processes++;
		process = process->next;
	}
	return (num_processes);
}

static void	parent_execution(t_process *process, int i, int num_processes)
{
	if (i != 0)
		close_pipes(process->prev->fd);
	if (i == num_processes - 1)
		close_pipes(process->fd);
}

static void	child_execution(t_process *process, t_env *env,
			t_builtin functions[])
{
	set_child_signals();
	if (process->outfile == STDOUT_FILENO && process->next)
		dup2(process->fd[1], STDOUT_FILENO);
	else
		dup2(process->outfile, STDOUT_FILENO);
	if (process->prev && process->infile == STDIN_FILENO)
	{
		dup2(process->prev->fd[0], STDIN_FILENO);
		close_pipes(process->prev->fd);
	}
	else
	{
		dup2(process->infile, STDIN_FILENO);
		if (process->prev)
			close_pipes(process->prev->fd);
	}
	close_pipes(process->fd);
	last_exit = execute_builtins(process->cmd, env, functions);
	if (last_exit == -1)
	{
		execve(get_path(process->cmd, *env), process->cmd,
			get_env_array(*env));
		exit(EXIT_FAILURE);
	}
	exit(last_exit);
}

int	check_path(char *path, t_process *process)
{
	if (!path || access(path, X_OK))
	{
		if (process->prev)
			close_pipes(process->prev->fd);
		if (!path)
			print_cmd_not_found(process->cmd[0]);
		else
			ft_perror(process->cmd[0], NULL, 127);
		if (!process->next)
			return (127);
		return (0);
	}
	return (1);
}

int	main_execution(t_process *process, t_env *env, int num_arr[2],
		t_builtin functions[])
{
	char	*path;
	int		check;

	if (!process->cmd || !process->cmd[0] || !process->cmd[0][0]) // remover os ultimos dois quando arrumar a expansao...
		return (0);
	if (!is_builtins(process->cmd, functions))
	{
		path = get_path(process->cmd, *env);
		check = check_path(path, process);
		if (path)
			free(path);
		if (check == 0 || check == 127)
			return (check);
	}
	check = fork();
	if (check == -1)
		exit(EXIT_FAILURE);
	if (check == CHILD)
		child_execution(process, env, functions);
	else
		parent_execution(process, num_arr[1], num_arr[0]);
	return (0);
}
