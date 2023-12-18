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

// Função de entrada para a execução de comandos
// Recebe	o(s) processo(s) e executa
// Primeiro ve se existe mais de um processo:
// 	1 processo: executa o redirection (se existe) do stdout
//		e executa esse comando com a função execute_single_cmd
// 	+ de 1 processo: executa a função execute_multi_cmd
//		que vai controlar os pipes e redirections
// Return: O valor de saida do programa executado
int	execute_cmd(t_process *process, t_env *envp, int last_exit,
		t_builtin functions[])
{
	if (!process->next)
		return (execute_single_cmd(process, envp, last_exit, functions));
	else
		return (execute_multi_cmd(process, envp, last_exit, functions));
}
