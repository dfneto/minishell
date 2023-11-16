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

char	*get_path(char **cmd)
{
	char	*abs_path;
	char	**paths;
	int		i;

	i = 0;
	abs_path = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!abs_path)
		return (NULL);
	ft_strlcat(abs_path, cmd[0], PATH_MAX);
	if (!access(abs_path, X_OK))
		return (abs_path);
	paths = ft_split(getenv("PATH"), ':');
	if (paths)
	{
		while (paths[i])
		{
			ft_bzero(abs_path, PATH_MAX);
			ft_strlcpy(abs_path, paths[i], ft_strlen(paths[i]) + 1);
			ft_strlcat(abs_path, "/", PATH_MAX);
			ft_strlcat(abs_path, cmd[0], PATH_MAX);
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

int	is_executable(char **cmd, char **envp)
{
	char	*path;

	path = get_path(cmd);
	if (path == NULL)
	{
		print_error("Brazilian Shell: ");
		print_error(cmd[0]);
		print_error(": command not found\n");
		exit (127);
	}
	execve(path, cmd, envp);
	exit(EXIT_FAILURE);
}

void	child_pipes(t_process *process)
{
	if (process->prev)
	{
		dup2(process->prev->fd[0], 0);
		close(process->prev->fd[0]);
		close(process->prev->fd[1]);
	}
	if (process->next)
	{
		close(process->fd[0]);
		dup2(process->fd[1], 1);
		close(process->fd[1]);
	}	
}

int	execute_single_cmd(char **cmd, char ***env, int last_exit, t_builtin functions[])
{
	int	fork_id;
	
	last_exit = execute_builtins(cmd, env, last_exit, functions);
	if (last_exit == -1)
	{
		fork_id = fork();
		if (fork_id < 0)
			exit(EXIT_FAILURE);
		if (fork_id == CHILD)
			is_executable(cmd, *env);
		else
		{
			wait(&last_exit);
			last_exit = WEXITSTATUS(last_exit);
		}
	}
	return (last_exit);
}

int	execute_multi_cmd(t_process *process, char ***env, int last_exit, t_builtin functions[])
{
	int	check;
	int	num_proc;
	int	i;
	t_process *current;

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
			exit (EXIT_FAILURE);
		check = fork();
		if (check == -1)
			exit (EXIT_FAILURE);
		if (check == CHILD)
		{
			if (i != 0)
			{
				dup2(process->prev->fd[0], STDIN_FILENO);
				close(process->prev->fd[0]);
				close(process->prev->fd[1]);
			}
			if (i != num_proc - 1)
			{
				dup2(process->fd[1], STDOUT_FILENO);
			}
			close(process->fd[1]);
			close(process->fd[0]);
			exit(execute_single_cmd(process->cmd, env, last_exit, functions));
		}
		else
		{
			if (i != 0)
			{
				close(process->prev->fd[0]);
				close(process->prev->fd[1]);
			}
			if (i == num_proc - 1)
			{
				close(process->fd[1]);
				close(process->fd[0]);
			}
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
/* 	while (process)
	{
		if (process->next)
		{
			check = pipe(process->fd);
			if (check == -1)
				exit(EXIT_FAILURE);
		}
		check = fork();
		if (check < 0)
			exit(EXIT_FAILURE);
		if (check == CHILD)
		{
			child_pipes(process);
			exit(execute_single_cmd(process->cmd, env, last_exit, functions));
		}
		else
		{
			if (process->prev)
			{
				close(process->prev->fd[0]);
				close(process->prev->fd[1]);
			}
			wait(&last_exit);
			last_exit = WEXITSTATUS(last_exit);
		}
		process = process->next;
	} */
	return (last_exit);
}

int	execute_cmd(t_process *process, char ***envp,
		int last_exit, t_builtin functions[])
{
	if (!process->next)
		return (execute_single_cmd(process->cmd, envp, last_exit, functions));
	else
		return (execute_multi_cmd(process, envp, last_exit, functions));
}
