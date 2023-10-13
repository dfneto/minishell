/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:34:20 by davifern          #+#    #+#             */
/*   Updated: 2023/10/13 13:43:05 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Ideally the lexical analysis does more stuffs than
* allocate tokens, but in this brazilian shell version
* it just produces a list of tokens
*/
t_token	*lexical_analysis(char *input)
{
	return (create_tokens(input));
}

/*
* Create a token of type DOUB_QUOTE_TYPE or SING_QUOTE_TYPE
* and add it to the end of token list (first_token)
*/
void	create_quote_tok_add_back(t_token **first_token, char *input, int *i)
{
	if (input[*i] == DOUB_QUOTE_CHAR)
		add_token(first_token,
			create_quote_token(input, i, DOUB_QUOTE_TYPE, DOUB_QUOTE_CHAR));
	else
		add_token(first_token,
			create_quote_token(input, i, SING_QUOTE_TYPE, SING_QUOTE_CHAR));
}

/*
* Other can be space or pipe, in this way, it
* creates a token of type SPACE_TYPE or PIPE_TYPE
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
		add_token(root,
			create_redirec_tok(input, i, APPEND_TYPE, GREATER_CHAR));
	else if (input[*i] == GREATER_CHAR)
		add_token(root,
			create_redirec_tok(input, i, OUTPUT_REDIREC_TYPE, GREATER_CHAR));
	else if (input[*i] == LESS_CHAR && input[*i + 1] == LESS_CHAR)
		add_token(root, create_redirec_tok(input, i, HERE_DOC_TYPE, LESS_CHAR));
	else
		add_token(root,
			create_redirec_tok(input, i, INPUT_REDIRECTION_TYPE, LESS_CHAR));
}

/*
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		
* 5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
t_token	*create_tokens(char *input)
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
