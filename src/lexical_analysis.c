/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:34:20 by davifern          #+#    #+#             */
/*   Updated: 2023/10/12 19:59:07 by davifern         ###   ########.fr       */
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
	return (tokenization(input));
}

/*
* Create a token of type DOUB_QUOTE_TYPE or SING_QUOTE_TYPE
* and add it to the end of token list (first_token)
*/
void	create_quote_and_add_back(t_token **first_token, char *input, int *i)
{
	if (input[*i] == DOUB_QUOTE_ASCII)
		add_token_back(first_token,
			create_quote_token(input, i, DOUB_QUOTE_TYPE, DOUB_QUOTE_ASCII));
	else
		add_token_back(first_token,
			create_quote_token(input, i, SING_QUOTE_TYPE, SING_QUOTE_ASCII));
}

/*
* Other can be space or pipe, in this way, it
* creates a token of type SPACE_TYPE or PIPE_TYPE
* and add it to the end of token list (first_token)
*/
void	create_other_and_add_back(t_token **first_token, char *input, int *i)
{
	if (input[*i] == SPACE_ASCII)
		add_token_back(first_token, create_space_token(input, i));
	else
		add_token_back(first_token, create_pipe_token(input, i));
}

void	create_redirec_and_add_back(t_token **first_token, char *input, int *i)
{create_generic_to
	if (input[*i] == GREATER_ASCII && input[*i + 1] == GREATER_ASCII)
		add_token_back(first_token, create_generic_token(input, i, APPEND_TYPE, GREATER_ASCII));
	else if (input[*i] == GREATER_ASCII)
		add_token_back(first_token, create_generic_token(input, i, OUTPUT_REDIRECTION_TYPE, GREATER_ASCII));
	else if (input[*i] == LESS_ASCII && input[*i + 1] == LESS_ASCII)
		add_token_back(first_token, create_generic_token(input, i, HERE_DOC_TYPE, LESS_ASCII));
	else
		add_token_back(first_token, create_generic_token(input, i, INPUT_REDIRECTION_TYPE, LESS_ASCII));
}

/*
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		
* 5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
t_token	*tokenization(char *input)
{
	int		i;
	t_token	*first_token;

	i = 0;
	first_token = NULL;
	while (input[i])
	{
		if (input[i] == DOUB_QUOTE_ASCII || input[i] == SING_QUOTE_ASCII)
			create_quote_and_add_back(&first_token, input, &i);
		else if (input[i] == SPACE_ASCII || input[i] == PIPE_ASCII)
			create_other_and_add_back(&first_token, input, &i);
		else if (input[i] == GREATER_ASCII || input[i] == LESS_ASCII)
			create_redirec_and_add_back(&first_token, input, &i);
		else
			add_token_back(&first_token, create_string_token(input, &i));
	}
	return (first_token);
}
