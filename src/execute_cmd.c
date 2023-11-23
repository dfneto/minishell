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

void	clean_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void print_path(char *path)
{
	int return_val;

	errno = 0;
	return_val = access(path, F_OK);
	printf("PATH: %s - F_OK: %d - errno: %d\n", path, return_val, errno);
	return_val = access(path, X_OK);
	printf("PATH: %s - X_OK: %d - errno: %d\n", path, return_val, errno);
}

int	is_cmd_executable(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

char	*get_path(char **cmd, t_env env, int last_exit)
{
	char	*abs_path;
	char	**paths;
	int		i;

	i = 0;
	abs_path = (char *)ft_calloc(PATH_MAX, sizeof(char));
	if (!abs_path)
		return (NULL);
	if (is_cmd_executable(cmd[0]))
	{
		ft_strlcat(abs_path, cmd[0], PATH_MAX);
		//printf("CMD: %s\n", cmd[0]);
		//print_path(abs_path);
		if (!access(abs_path, X_OK))
			return (abs_path);
	}
	paths = ft_split(ft_getenv("PATH", env, last_exit), ':');
	if (paths)
	{
		while (paths[i])
		{
			ft_bzero(abs_path, PATH_MAX);
			ft_strlcpy(abs_path, paths[i], ft_strlen(paths[i]) + 1);
			ft_strlcat(abs_path, "/", PATH_MAX);
			ft_strlcat(abs_path, cmd[0], PATH_MAX);
			//print_path(abs_path);
			if (!access(abs_path, X_OK))
			{
				clean_array(paths);
				return (abs_path);
			}
			i++;
		}
		clean_array(paths);
		free(abs_path);
	}
	return (NULL);
}

int	is_executable(char **cmd, t_env envp, int last_exit)
{
	char	*path;

	path = get_path(cmd, envp, last_exit);
	if (path == NULL)
	{
		print_error("Brazilian Shell: ");
		print_error(cmd[0]);
		print_error(": command not found\n");
		exit(127);
	}
	//Converter t_env em array e trocar no NULL abaixo
	execve(path, cmd, NULL);
	exit(EXIT_FAILURE);
}

/* 
REFACTOR
FORK desnecessario... as vezes
*/
int	execute_single_cmd(char **cmd, t_env *env, int last_exit,
		t_builtin functions[])
{
	int	fork_id;

	last_exit = execute_builtins(cmd, env, last_exit, functions);
	if (last_exit == -1)
	{
		fork_id = fork();
		if (fork_id < 0)
			exit(EXIT_FAILURE);
		if (fork_id == CHILD)
			is_executable(cmd, *env, last_exit);
		else
		{
			wait(&last_exit);
			last_exit = WEXITSTATUS(last_exit);
		}
	}
	return (last_exit);
}

void	close_pipes(int pipe[])
{
	close(pipe[0]);
	close(pipe[1]);
}

/* 
REFACTOR
TOO FUCKING BIG
*/
int	execute_multi_cmd(t_process *process, t_env *env, int last_exit,
		t_builtin functions[])
{
	int			check;
	int			num_proc;
	int			i;
	t_process	*current;

	current = process;
	num_proc = 0;
	while (current != NULL)
	{
		num_proc += 1;
		current = current->next;
	}
	i = 0;
	while (i < num_proc)
	{
		if (pipe(process->fd) == -1)
			exit(EXIT_FAILURE);
		check = fork();
		if (check == -1)
			exit(EXIT_FAILURE);
		if (check == CHILD)
		{
			if (i != 0)
			{
				dup2(process->prev->fd[0], STDIN_FILENO);
				close_pipes(process->prev->fd);
			}
			if (i != num_proc - 1)
			{
				dup2(process->fd[1], STDOUT_FILENO);
			}
			else
			{
				dup2(process->outfile, STDOUT_FILENO);
			}
			close_pipes(process->fd);
			exit(execute_single_cmd(process->cmd, env, last_exit, functions));
		}
		else
		{
			if (i != 0)
				close_pipes(process->prev->fd);
			if (i == num_proc - 1)
				close_pipes(process->fd);
		}
		process = process->next;
		i++;
	}
	i = 0;
	while (i < num_proc)
	{
		wait(&last_exit);
		i++;
	}
	last_exit = WEXITSTATUS(last_exit);
	return (last_exit);
}

int	execute_cmd(t_process *process, t_env *envp, int last_exit,
		t_builtin functions[])
{
	int	og_stdout;

	og_stdout = -1;
	if (!process->next)
	{
		if (process->outfile != STDOUT_FILENO)
		{
			og_stdout = dup(STDOUT_FILENO);
			dup2(process->outfile, STDOUT_FILENO);
		}
		last_exit = execute_single_cmd(process->cmd, envp, last_exit,
				functions);
		if (og_stdout >= 0)
			dup2(og_stdout, STDOUT_FILENO);
		return (last_exit);
	}
	else
		return (execute_multi_cmd(process, envp, last_exit, functions));
}
