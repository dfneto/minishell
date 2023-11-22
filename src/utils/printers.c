/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:30 by davifern          #+#    #+#             */
/*   Updated: 2023/11/10 20:31:00 by davifern         ###   ########.fr       */
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
	printf("token values:\n");
	while (root)
	{
		if (root->str)
			printf("<%s>\n", root->str);
		else
			print_type(root->type);
		root = root->next;
	}
}