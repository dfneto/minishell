/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:39:42 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 11:08:16 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_space_token(char *input, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] == SPACE_CHAR)
		(*i)++;
	return (create_token(input, start, *i, SPC));
}

t_token	*create_pipe_token(char *input, int *i)
{
	(*i)++;
	return (create_token(input, 0, 0, PIPE));
}

/*
* We create the quote token with quote type and with 
* the content WITHOUT the history_quotes_inhibit_expansion
*/
t_token	*create_quote_token(char *input, int *i, int type, int quote_char)
{
	int		start;
	t_token	*tok;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	tok = create_token(input, start, *i, type);
	(*i)++;
	return (tok);
}

/*
 * Create a redirection token that can be:
 * output redirection, append,
 * input redirection or here doc
 */
t_token	*create_redirec_tok(char *input, int *i, int type, int quote_char)
{
	(*i)++;
	if (input[*i] == quote_char)
		(*i)++;
	return (create_token(input, 0, 0, type));
}

t_token	*create_string_token(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != DOUB_QUOTE_CHAR
		&& input[*i] != SING_QUOTE_CHAR && input[*i] != SPACE_CHAR
		&& input[*i] != GREATER_CHAR && input[*i] != LESS_CHAR
		&& input[*i] != PIPE_CHAR)
		(*i)++;
	return (create_token(input, start, *i - 1, STRING));
}
