/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:34:20 by davifern          #+#    #+#             */
/*   Updated: 2023/10/12 17:57:06 by davifern         ###   ########.fr       */
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
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
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
		if (input[i] == DOUB_QUOTE_ASCII)
			add_node_back(&first_token, create_quote_token(input, &i, DOUB_QUOTE_TYPE, DOUB_QUOTE_ASCII));
		else if (input[i] == SING_QUOTE_ASCII)
			add_node_back(&first_token, create_quote_token(input, &i, SING_QUOTE_TYPE, SING_QUOTE_ASCII));
		else if (input[i] == SPACE_ASCII)
			add_node_back(&first_token, create_space_token(input, &i));
		else if (input[i] == PIPE_ASCII)
			add_node_back(&first_token, create_pipe_token(input, &i));
		else if (input[i] == OUTPUT_REDIRECTION_ASCII && input[i+1] == OUTPUT_REDIRECTION_ASCII)
			add_node_back(&first_token, create_generic_token(input, &i, APPEND_TYPE, OUTPUT_REDIRECTION_ASCII));
		else if (input[i] == OUTPUT_REDIRECTION_ASCII)
			add_node_back(&first_token, create_generic_token(input, &i, OUTPUT_REDIRECTION_TYPE, OUTPUT_REDIRECTION_ASCII));
		else if (input[i] == INPUT_REDIRECTION_ASCII && input[i+1] == INPUT_REDIRECTION_ASCII)
			add_node_back(&first_token, create_generic_token(input, &i, HERE_DOC_TYPE, INPUT_REDIRECTION_ASCII));
		else if (input[i] == INPUT_REDIRECTION_ASCII)
			add_node_back(&first_token, create_generic_token(input, &i, INPUT_REDIRECTION_TYPE, INPUT_REDIRECTION_ASCII));
		else
			add_node_back(&first_token, create_string_token(input, &i));
	}
	return (first_token);
}
