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

static void	set_single_redirects(t_process *process, int *og_stdin,
			int *og_stdout)
{
	if (process->outfile != STDOUT_FILENO)
	{
		*og_stdout = dup(STDOUT_FILENO);
		dup2(process->outfile, STDOUT_FILENO);
	}
	if (process->infile != STDIN_FILENO)
	{
		*og_stdin = dup(STDIN_FILENO);
		dup2(process->infile, STDIN_FILENO);
	}
}

static void	reset_redirects(t_process *process, int *og_stdin, int *og_stdout)
{
	if (process->outfile != STDOUT_FILENO)
	{
		dup2(*og_stdout, STDOUT_FILENO);
		close(*og_stdout);
	}
	if (process->infile != STDIN_FILENO)
	{
		dup2(*og_stdin, STDIN_FILENO);
		close(*og_stdin);
	}
}

static void	child_execution(char *path, char **argv, t_env env)
{
	execve(path, argv, get_env_array(env));
	exit(EXIT_FAILURE);
}

static int parent_execution(char *path)
{
	int	child_exit;

	free(path);
	wait(&child_exit);
	return (WEXITSTATUS(child_exit));
}

int	execute_single_cmd(t_process *process, t_env *env, int last_exit,
		t_builtin functions[])
{
	int		fork_id;
	int		og_stdout;
	int		og_stdin;
	char	*path;

	if (process->outfile == -1 || process->infile == -1)
		return (1);
	set_single_redirects(process, &og_stdin, &og_stdout);
	last_exit = execute_builtins(process->cmd, env, last_exit, functions);
	if (last_exit == -1)
	{
		path = get_path(process->cmd, *env);
		if (path == NULL)
		{
			reset_redirects(process, &og_stdin, &og_stdout);
			return (print_cmd_not_found(process->cmd[0]));
		}
		fork_id = fork();
		if (fork_id < 0)
			exit(EXIT_FAILURE);
		if (fork_id == CHILD)
			child_execution(path, process->cmd, *env);
		else
			last_exit = parent_execution(path);
	}
	reset_redirects(process, &og_stdin, &og_stdout);
	return (last_exit);
}
