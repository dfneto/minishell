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

static int	count_processes(t_process *process)
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

static void	parent_execution(t_process *process, int i, int num_processes,
			char *path)
{
	if (i != 0)
		close_pipes(process->prev->fd);
	if (i == num_processes - 1)
		close_pipes(process->fd);
	free(path);
}

static void	child_execution(t_process *process, int last_exit, t_env *env,
			t_builtin functions[])
{
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
	last_exit = execute_builtins(process->cmd, env, last_exit,
			functions);
	if (last_exit == -1)
	{
		execve(get_path(process->cmd, *env), process->cmd,
			get_env_array(*env));
		exit(EXIT_FAILURE);
	}
	exit(last_exit);
}

static int	main_execution(t_process *process, t_env *env, int num_arr[3],
		t_builtin functions[])
{
	char	*path;
	int		check;

	path = get_path(process->cmd, *env);
	if (!is_builtins(process->cmd, functions) && !path)
	{
		if (process->prev)
			close_pipes(process->prev->fd);
		num_arr[2] = print_cmd_not_found(process->cmd[0]);
		if (!process->next)
			return (num_arr[2]);
	}
	else
	{
		check = fork();
		if (check == -1)
			exit(EXIT_FAILURE);
		if (check == CHILD)
			child_execution(process, num_arr[2], env, functions);
		else
			parent_execution(process, num_arr[1], num_arr[0], path);
	}
	return (0);
}
/*
Função que faz a execução de varios comandos, realizando os pipes e redirections
Necessita revisão
REFACTOR
TOO FUCKING BIG

VERIFICAR REDIRECTS E HEREDOC
ORGANIZAR PIPES
*/

int	execute_multi_cmd(t_process *process, t_env *env, int last_exit,
		t_builtin functions[])
{
	int	num_arr[3];

	num_arr[0] = count_processes(process);
	num_arr[1] = 0;
	num_arr[2] = last_exit;
	while (process)
	{
		if (pipe(process->fd) == -1)
			exit(EXIT_FAILURE);
		if (process->outfile == -1 || process->infile == -1)
			last_exit = 1;
		else
			if (main_execution(process, env, num_arr, functions))
				return (127);
		process = process->next;
		num_arr[1]++;
	}
	num_arr[1] = 0;
	while (num_arr[1] < num_arr[0])
	{
		wait(&last_exit);
		num_arr[1]++;
	}
	last_exit = WEXITSTATUS(last_exit);
	return (last_exit);
}
