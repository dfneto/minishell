/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/01/19 18:27:41 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type(int type)
{
	if (type == SPC)
		return ("spc");
	else if (type == OUTPUT_REDIRECTION)
		return (">");
	else if (type == APPEND)
		return (">>");
	else if (type == INPUT_REDIRECTION)
		return ("<");
	else if (type == HERE_DOC)
		return ("<<");
	else if (type == PIPE)
		return ("|");
	else
		return ("nothing to be printed");
}

void	print_list_token(t_token *token)
{
	if (!token)
		printf("Token nulo\n");
	while (token)
	{
		print_token(token);
		token = token->next;
	}
}

void	print_token(t_token *token)
{
	if (token->str)
		printf("Token type: %s -> str: <%s>\n",
			get_type(token->type), token->str);
	else
		printf("Token type: %s\n", get_type(token->type));
}
