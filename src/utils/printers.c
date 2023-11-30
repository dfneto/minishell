/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:30 by davifern          #+#    #+#             */
/*   Updated: 2023/11/30 23:41:34 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type(int type)
{
	if (type == SPC)
		printf("spc\n");
	else if (type == OUTPUT_REDIRECTION)
		printf(">\n");
	else if (type == APPEND)
		printf(">>\n");
	else if (type == INPUT_REDIRECTION)
		printf("<\n");
	else if (type == HERE_DOC)
		printf("<<\n");
	else if (type == PIPE)
		printf("|\n");
	else
		printf("nothing to be printed\n");
}

void	print_list(t_token *root)
{
	while (root)
	{
		if (root->str)
			printf("<%s>\n", root->str);
		else
			print_type(root->type);
		root = root->next;
	}
}

void	print_process(t_process *process)
{
	int	i;

	i = 0;
	printf("Process created:\n");
	while (process->cmd[i])
	{
		printf("%s\n", process->cmd[i]);
		i++;
	}
}

void	print_redirect(t_redirect *redirect)
{
	printf("Imprimindo as redireções ...\n");
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

void	print_process_list(t_process *root)
{
	int i;
	
	i = 0;
	printf("Imprimindo os processos ...\n");
	if (!root)
		printf("Lista de processos nula ...\n");
	while (root)
	{
		printf("processo: ");
		while (root->cmd[i])
		{
			printf("%s ", root->cmd[i]);
			i++;
		}
		printf("\n");
		printf("outfile: %d\n", root->outfile);
		printf("infile: %d\n", root->infile);
		print_redirect(root->redirect);
		root = root->next;
	}
}
