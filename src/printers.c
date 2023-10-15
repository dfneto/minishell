/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:30 by davifern          #+#    #+#             */
/*   Updated: 2023/10/15 12:38:53 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type(int type)
{
	if (type == SPACE_TYPE)
		printf("spc\n");
	else if (type == OUTPUT_REDIREC_TYPE)
		printf(">\n");
	else if (type == APPEND_TYPE)
		printf(">>\n");
	else if (type == INPUT_REDIRECTION_TYPE)
		printf("<\n");
	else if (type == HERE_DOC_TYPE)
		printf("<<\n");
	else if (type == PIPE_TYPE)
		printf("|\n");
	else
		printf("nothing to be printed\n");
}

void	print_list(t_token *root)
{
	printf("token value:\n");
	while (root)
	{
		if (root->str)
			printf("%s\n", root->str);
		else
			print_type(root->type);
		root = root->next;
	}
}
