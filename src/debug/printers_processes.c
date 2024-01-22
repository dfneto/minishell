/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 17:37:49 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(char **cmd)
{
	int	i;

	if (!cmd)
	{
		printf("CMD NULL\n");
		return ;
	}
	printf("CMD not NULL\n");
	i = 0;
	if (!cmd[i])
	{
		printf("CMD[%d] NULL", i);
		return ;
	}
	while (cmd[i])
	{
		printf("CMD[%d] -> %s\n", i, cmd[i]);
		i++;
	}
}

void	print_process(t_process *process)
{
	int	i;

	i = 0;
	if (process == NULL)
	{
		printf("Process NULL\n");
		return ;
	}
	printf("Processo nao eh nulo\n");
	print_cmd(process->cmd);
	print_list_redirect(process->redirect);
}

void	print_list_redirect(t_redirect *redirect)
{
	printf("Imprimindo as redireções ...\n");
	if (!redirect)
		printf("Redirect is NULL\n");
	while (redirect)
	{
		printf("redirect: ");
		if (redirect->type == OUTPUT_REDIRECTION)
			printf("> ");
		else if (redirect->type == APPEND)
			printf(">> ");
		else if (redirect->type == INPUT_REDIRECTION)
			printf("< ");
		else if (redirect->type == HERE_DOC)
			printf("<< ");
		printf("- file name: %s\n", redirect->name);
		redirect = redirect->next;
	}
}

void	print_list_process(t_process *root)
{
	int	i;

	i = 0;
	printf("Imprimindo os processos ...\n");
	if (!root)
		printf("Lista de processos nula ...\n");
	while (root)
	{
		print_process(root);
		root = root->next;
	}
}
