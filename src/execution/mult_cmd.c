/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:35:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/22 16:31:28 by lsulzbac         ###   ########.fr       */
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

static int	start_processes(t_process *process, t_env *env,
		t_builtin functions[])
{
	while (process)
	{
		if (pipe(process->fd) == -1)
			exit(EXIT_FAILURE);
		if (process->outfile == -1 || process->infile == -1 || process->errfile == -1) // stderr
			env->last_exit = 1;
		else
			if (main_execution(process, env, functions))
				return (127);
		process = process->next;
	}
	return (0);
}

static int	wait_for_processes(int num_processes)
{
	int	checker;
	int	last_ok_exit;
	int	i;
	int	exit_value;

	checker = 0;
	last_ok_exit = 0;
	i = 0;
	exit_value = 0;
	while (i < num_processes)
	{
		wait(&exit_value);
		if (WIFEXITED(exit_value))
		{
			checker = 1;
			last_ok_exit = WEXITSTATUS(exit_value);
		}
		else if (!checker && WIFSIGNALED(exit_value))
			exit_value = 128 + WTERMSIG(exit_value);
		i++;
	}
	if (checker)
		exit_value = last_ok_exit;
	return (exit_value);
}

/*
Função que faz a execução de varios comandos, realizando os pipes e redirections
Necessita revisão
REFACTOR
TOO FUCKING BIG

VERIFICAR REDIRECTS E HEREDOC
ORGANIZAR PIPES
*/

int	execute_multi_cmd(t_process *process, t_env *env,
		t_builtin functions[])
{
	int	num_processes;

	num_processes = count_processes(process);
	if (start_processes(process, env, functions))
		return (127);
	return (wait_for_processes(num_processes));
}
