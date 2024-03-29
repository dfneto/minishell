/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexical_analysis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:34:20 by davifern          #+#    #+#             */
/*   Updated: 2024/01/25 19:47:34 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Create a token of type DOUBLE_QUOTE or SINGLE_QUOTE
 * and add it to the end of token list (first_token)
 */
void	create_quote_tok_add_back(t_token **first_token, char *input, int *i)
{
	if (input[*i] == DOUB_QUOTE_CHAR)
		add_token(first_token, create_quote_token(input, i, DOUBLE_QUOTE,
				DOUB_QUOTE_CHAR));
	else
		add_token(first_token, create_quote_token(input, i, SINGLE_QUOTE,
				SING_QUOTE_CHAR));
}

/*
 * Other can be space or pipe, in this way, it
 * creates a token of type SPACE or PIPE
 * and add it to the end of token list (first_token)
 */
void	create_other_tok_add_back(t_token **first_token, char *input, int *i)
{
	if (input[*i] == SPACE_CHAR)
		add_token(first_token, create_space_token(input, i));
	else
		add_token(first_token, create_pipe_token(input, i));
}

void	create_redirec_tok_add_back(t_token **root, char *input, int *i)
{
	if (input[*i] == GREATER_CHAR && input[*i + 1] == GREATER_CHAR)
		add_token(root, create_redirec_tok(input, i, APPEND, GREATER_CHAR));
	else if (input[*i] == GREATER_CHAR)
		add_token(root, create_redirec_tok(input, i, OUTPUT_REDIRECTION,
				GREATER_CHAR));
	else if (input[*i] == LESS_CHAR && input[*i + 1] == LESS_CHAR)
		add_token(root, create_redirec_tok(input, i, HERE_DOC, LESS_CHAR));
	else
		add_token(root, create_redirec_tok(input, i, INPUT_REDIRECTION,
				LESS_CHAR));
}

/*
 * return: a pointer to a token that is chainned with others tokens
 * where each token pointes to the next
 * There are 9 types of token (see enum token_type).
 */
t_token	*create_all_tokens(char *input)
{
	int		i;
	t_token	*first_token;

	i = 0;
	first_token = NULL;
	while (input[i])
	{
		if (input[i] == DOUB_QUOTE_CHAR || input[i] == SING_QUOTE_CHAR)
			create_quote_tok_add_back(&first_token, input, &i);
		else if (input[i] == SPACE_CHAR || input[i] == PIPE_CHAR)
			create_other_tok_add_back(&first_token, input, &i);
		else if (input[i] == GREATER_CHAR || input[i] == LESS_CHAR)
			create_redirec_tok_add_back(&first_token, input, &i);
		else
			add_token(&first_token, create_string_token(input, &i));
	}
	return (first_token);
}

/*
 * Ideally the lexical analysis does more stuffs than
 * allocate tokens, but in this shell
 * it just produces a list of tokens.
 * Here it also remove the quotes
 */
t_token	*lexical_analysis(char *input, t_env *env)
{
	t_token	*first_token;

	first_token = create_all_tokens(input);
	if (validate_tokens(first_token))
	{
		env->last_exit = 2;
		clean_tokens(first_token);
		return (NULL);
	}
	if (g_signal != 0)
	{
		env->last_exit = 128 + g_signal;
		g_signal = 0;
	}
	expansion(first_token, *env);
	return (first_token);
}
