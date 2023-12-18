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
static int	execute_multi_cmd(t_process *process, t_env *env, int last_exit,
		t_builtin functions[])
{
	int			check;
	int			num_proc;
	int			i;
	t_process	*current;
	char		*path;

	current = process;
	num_proc = 0;
	while (current != NULL)
	{
		num_proc += 1;
		current = current->next;
	}
	i = 0;
	while (process)
	{
		if (pipe(process->fd) == -1)
			exit(EXIT_FAILURE);
		if (process->outfile == -1 || process->infile == -1)
			last_exit = 1;
		else
		{
			path = get_path(process->cmd, *env);
			if (!is_builtins(process->cmd, functions) && !path)
			{
				if (process->prev)
					close_pipes(process->prev->fd);
				last_exit = print_cmd_not_found(process->cmd[0]);
	 			if (!process->next)
					return (last_exit);
			}
			else
			{
				check = fork();
				if (check == -1)
					exit(EXIT_FAILURE);
				if (check == CHILD)
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
				else
				{
					if (i != 0)
						close_pipes(process->prev->fd);
					if (i == num_proc - 1)
						close_pipes(process->fd);
				}
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
	return (last_exit);
}

/*
Função de entrada para a execução de comandos
Recebe	o(s) processo(s) e executa
Primeiro ve se existe mais de um processo:
	1 processo: executa o redirection (se existe) do stdout e executa esse comando com a função execute_single_cmd
	+ de 1 processo: executa a função execute_multi_cmd que vai controlar os pipes e redirections
Return: O valor de saida do programa executado
*/
int	execute_cmd(t_process *process, t_env *envp, int last_exit,
		t_builtin functions[])
{
	if (!process->next)
		return (execute_single_cmd(process, envp, last_exit, functions));
	else
		return (execute_multi_cmd(process, envp, last_exit, functions));
}
