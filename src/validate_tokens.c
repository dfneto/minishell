/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:37 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/28 16:19:40 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	print_validate_error(t_type error_type)
{
	print_error("Brazilian Shell: syntax error near unexpected token `");
	if (error_type == PIPE)
		print_error("|");
	else if (error_type == OUTPUT_REDIRECTION)
		print_error(">");
	else if (error_type == OUTPUT_REDIRECTION)
		print_error(">");
	else if (error_type == APPEND)
		print_error(">>");
	else if (error_type == INPUT_REDIRECTION)
		print_error("<");
	else if (error_type == HERE_DOC)
		print_error("<<");
	else if (error_type == NL)
		print_error("newline");
	print_error("\'\n");
	return (1);
}

int	validate_tokens(t_token *token)
{
	int	cmd;

	cmd = 0;
	while (token)
	{
		if (!(token->str || token->type == SPC))
		{
			if (token->type == PIPE && !cmd)
				return (print_validate_error(token->type));
			cmd = 0;
			token = token->next;
			while (token && token->type == SPC)
				token = token->next;
			if (token && !token->str)
				return (print_validate_error(token->type));
			if (!token)
				return (print_validate_error(NL));
			cmd = 1;
		}
		else if (token->str)
			cmd = 1;
		token = token->next;
	}
	return (0);
}
