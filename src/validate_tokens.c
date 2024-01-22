/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:37 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:00 by lsulzbac         ###   ########.fr       */
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

static int	validate_helper(t_token *token, int *cmd)
{
	int	pipe;

	pipe = 0;
	if (token->type == PIPE && !(*cmd))
		return (print_validate_error(token->type));
	if (token->type == PIPE)
		pipe = 1;
	*cmd = 0;
	token = token->next;
	while (token && token->type == SPC)
		token = token->next;
	if (!token)
		return (0);
	if (pipe && token->type != PIPE)
		pipe = 0;
	else if (token && !token->str)
		return (print_validate_error(token->type));
	return (0);
}

int	validate_tokens(t_token *token)
{
	int	cmd;

	cmd = 0;
	if (token && token->type == SPC && !token->next)
		return (0);
	while (token)
	{
		if (!(token->str || token->type == SPC))
		{
			if (validate_helper(token, &cmd))
				return (1);
		}
		if (token && token->str)
			cmd = 1;
		if (token)
			token = token->next;
	}
	if (!token && !cmd)
		return (print_validate_error(NL));
	return (0);
}
