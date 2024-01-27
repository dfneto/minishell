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

void	set_single_redirects(t_process *process, int *og_stdin, int *og_stdout, int *og_stderr)
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
	if (process->errfile != STDERR_FILENO)
	{
		*og_stderr = dup(STDERR_FILENO);
		dup2(process->errfile, STDERR_FILENO);
	}
}

void	reset_redirects(t_process *process, int *og_stdin, int *og_stdout, int *og_stderr)
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
	if (process->errfile != STDERR_FILENO)
	{
		dup2(*og_stderr, STDERR_FILENO);
		close(*og_stderr);
	}
}

static void	child_execution(char *path, char **argv, t_env env)
{
	set_child_signals();
	execve(path, argv, get_env_array(env));
	exit(EXIT_SUCCESS);
}

static int	parent_execution(void)
{
	int	child_exit;

	wait(&child_exit);
	if (WIFEXITED(child_exit))
		return (WEXITSTATUS(child_exit));
	return (128 + WTERMSIG(child_exit));
}

int	do_single_fork(char *path, char **cmd, t_env env)
{
	int	fork_id;

	fork_id = fork();
	if (fork_id < 0)
		exit(EXIT_FAILURE);
	if (fork_id == CHILD)
		child_execution(path, cmd, env);
	else
		return (parent_execution());
	return (EXIT_SUCCESS);
}
