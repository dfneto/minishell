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

/* int	is_builtin(char *exec)
{
	int	i;

	char *builtins[] = {"echo", "pwd", "exit", "env", "cd", "export", NULL};
	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(exec, builtins[i], ft_strlen(exec) + 1))
			return (i);
		i++;
	}
	return (-1);
} */

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

void	child_pipes(int has_prev, t_process *has_next, int pipes[4])
{
	if (has_prev)
	{
		dup2(pipes[0], 0);
		close(pipes[0]);
		close(pipes[1]);
	}
	if (has_next)
	{
		close(pipes[2]);
		dup2(pipes[3], 1);
		close(pipes[3]);
	}	
}

int	execute_cmd(t_process *current_process, char ***envp,
		unsigned char last_exit, t_builtin functions[])
{
	int	ret;
	int	pipes[4];
	//int	previous_pipe[2];
	int	fork_id;
	int	has_prev;
	int	has_pipe;
	int	pipe_value;

	ret = 0;
	has_pipe = 0;
	has_prev = 0;
	while (current_process)
	{
		if (current_process->next)
		{
			has_pipe = 1;
			pipe_value = pipe(pipes + 2);
			if (pipe_value == -1)
				exit(EXIT_FAILURE);
		}
		if (!has_pipe)
		{
			ret = execute_builtins(current_process->cmd, envp, last_exit, functions);
				if (ret == -1)
			{
				fork_id = fork();
				if (fork_id < 0)
					exit(EXIT_FAILURE);
				if (fork_id == CHILD)
					is_executable(current_process->cmd, *envp);
				else
				{
					wait(&ret);
					ret = WEXITSTATUS(ret);
				}
			}
		}
		else
		{
			fork_id = fork();
			if (fork_id < 0)
				exit(EXIT_FAILURE);
			if (fork_id == CHILD)
			{
				child_pipes(has_prev, current_process->next, pipes);
				ret = execute_builtins(current_process->cmd, envp, last_exit, functions);
				if (ret == -1)
					is_executable(current_process->cmd, *envp);
				exit(ret);
			}
			else
			{
				if (has_prev)
				{
					close(pipes[0]);
					close(pipes[1]);
				}
				wait(&ret);
				ret = WEXITSTATUS(ret);
				if (current_process->next)
				{
					has_prev = 1;
					pipes[0] = pipes[2];
					pipes[1] = pipes[3];
				}
			}
		}
		current_process = current_process->next;
	}
	return (ret);
}
