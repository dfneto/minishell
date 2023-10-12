/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:39:42 by davifern          #+#    #+#             */
/*   Updated: 2023/10/12 17:39:52 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_space_token(char *input, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] == SPACE_ASCII)
		(*i)++;
	return (create_token(input, start, *i, SPACE_TYPE));
}

t_token	*create_pipe_token(char *input, int *i)
{
	(*i)++;
	return (create_token(input, 0, 0, PIPE_TYPE));
}

t_token	*create_quote_token(char *input, int *i, int type, int quote_ascii)
{
	int		start;
	t_token	*tok;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote_ascii)
		(*i)++;
	tok = create_token(input, start, *i, type);
	(*i)++;
	return (tok);
}

t_token	*create_generic_token(char *input, int *i, int type, int quote_ascii)
{
	(*i)++;
	if (input[*i] == quote_ascii)
		(*i)++;
	return (create_token(input, 0, 0, type));
}

t_token	*create_string_token(char *input, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != DOUB_QUOTE_ASCII
		&& input[*i] != SING_QUOTE_ASCII
		&& input[*i] != SPACE_ASCII && input[*i] != OUTPUT_REDIRECTION_ASCII
		&& input[*i] != INPUT_REDIRECTION_ASCII && input[*i] != PIPE_ASCII)
		(*i)++;
	return (create_token(input, start, *i, STRING_TYPE));
}
