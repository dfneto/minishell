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
	int	num_arr[2];

	num_arr[0] = count_processes(process);
	num_arr[1] = 0;
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
