/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2024/01/21 20:23:36 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position,
		t_env env)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	if (token->str[*i] == '?')
	{
		(*i)++;
		return (get_exit_status());
	}
	while (token->str[*i] && is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = safe_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1);
	if (word_to_expand == NULL)
		return (safe_strdup(""));
	// printf("word to expand: %s\n", word_to_expand);
	return (safe_strdup(ft_getenv(word_to_expand, env)));
}

char	*expand_post_dollar(t_token *token, int *i, int dolar_position,
		t_env env)
{
	char	*word_expanded;
	char	*post_word;

	word_expanded = NULL;
	post_word = NULL;
	word_expanded = get_word_expanded(token, i, dolar_position, env);
	// printf("word to expand: %s\n", word_expanded);
		
	// joined = safe_strjoin(joined, word_expanded);
	// get_pos_word
	// if (token->str[*i] != '$') // para os casos 38, 39 e 40 echo "|$USER|"
	// {
	// 	post_word = safe_substr(token->str, *i, ft_strlen(token->str) - *i);
	// 	word_expanded = safe_strjoin(word_expanded, post_word);
	// }
	return (word_expanded);
}

/*
* cases: "$USER"
* 		 "123$USER" - with pre dolar
*		 "123$USER $USER"
* Others cases:
caso 1: echo "$USER" 				david 		- ok
caso 2: echo "$$USER"				$david 		- ok
caso 3: echo "$hola"								- ok
caso 4: echo "$$hola"				$			- ok
caso 5: echo "$""					$			- ok
caso 6: echo "$$""					$$			- ok
caso 8: echo "hi$"    				hi$     	- ok
caso 9: echo "hi$$"   				hi$$    	- ok
caso 13: echo "'$USER'"				'david'		- ok
caso 7: echo "$/"		     		$/      	- ok
caso 10: echo "hi$/"  				hi$/    	- ok
caso 11: echo "hi$$/"  				hi$$/ 		- ok
caso 12: echo "'$'"					'$'			- ok
caso 13: echo "$USER$PATH$PWD"		imprime...	- ok
*/
t_token	*expand_double_quote_token(t_token *token, t_env env)
{
	int		i;
	int		dolar_position;
	char	*pre_dolar;
	char	*joined;
	char	*word_expanded;
	char	*post_word;

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	word_expanded = NULL;
	post_word = NULL;
	
	// print_list_token(token);

	while (token->str[i] && dolar_position >= 0)
	{
		// pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
		joined = safe_strjoin(joined, get_pre_dolar_text(token->str, &dolar_position, i));
		if (dolar_position >= 0)
			i = dolar_position + 1;
		if (token->str[i] && dolar_position >= 0)
		{
			joined = safe_strjoin(joined, expand_post_dollar(token, &i, dolar_position, env));
			// printf("i: %d joined: %s\n", i, joined);
		}
		// {
		// 	word_expanded = get_word_expanded(token, &i, dolar_position, env);
			
		// 	joined = safe_strjoin(joined, word_expanded);
		// 	// get_pos_word
		// 	if (token->str[i] != '$') // para os casos 38, 39 e 40 echo "|$USER|"
		// 	{
		// 		post_word = safe_substr(token->str, i, ft_strlen(token->str) - i);
		// 		joined = safe_strjoin(joined, post_word);
		// 	}
		// }
		else if (token->str[i - 1] == '$') // para os casos 5 e 6
			joined = safe_strjoin(joined, "$");
	}
	// get_pos_last_word
	if (token->str[i] != '$') // para os casos 38, 39 e 40 echo "|$USER|"
	{
		post_word = safe_substr(token->str, i, ft_strlen(token->str) - i);
		joined = safe_strjoin(joined, post_word);
	}
	token->str = joined;
	// print_token(token);
	return (token);
}
