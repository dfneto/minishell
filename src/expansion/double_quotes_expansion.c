/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2024/01/19 23:14:48 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position,
		t_env env)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (token->str[*i] && is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = safe_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1);
	if (word_to_expand == NULL)
		return (safe_strdup(""));
	return (safe_strdup(ft_getenv(word_to_expand, env)));
}

/*
caso 1: $USER 				david 		- ok
caso 2: $$USER				$david 		- ok
caso 3: $hola						 	- ok
caso 4: $$hola				$			- ok
caso 5: $					$			- ok
caso 6: $$					$$			- ok
caso 8: echo "hi$"    		hi$     	- ok
caso 9: echo "hi$$"   		hi$$    	- ok
caso 13: echo "'$USER'"		'david'		- ok

caso 7: echo "$/"     $/      - ??? decidi não tratar porque não encontrei a lógica. Ex: hi$/ e hi$& imprimem igual, mas hi$!, hi$(, hi$* imprime outra coisa
caso 10: echo "hi$/"  hi$/    - decidi não tratar porque não encontrei a lógica. Ex: hi$/ e hi$& imprimem igual, mas hi$!, hi$(, hi$* imprime outra coisa
caso 11: echo "hi$$/"  hi$$/  - decidi não tratar porque não encontrei a lógica. Ex: hi$/ e hi$& imprimem igual, mas hi$!, hi$(, hi$* imprime outra coisa
caso 12: echo "'$'"
*/
//echo "$USER$PATH$PWD"
t_token	*expand_double_quote_token(t_token *token, t_env env)
{
	int i;
	int dolar_position;
	char *pre_dolar;
	char *joined;
	char *word_expanded;
	char *post_word;

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	word_expanded = NULL;
	post_word = NULL;
	while (token->str[i] && dolar_position >= 0)
	{
		pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
		joined = safe_strjoin(joined, pre_dolar);
		if (dolar_position >= 0)
			i = dolar_position + 1;
		if (token->str[i] && dolar_position >= 0)
		{
			word_expanded = get_word_expanded(token, &i,
						dolar_position, env);
			joined = safe_strjoin(joined, word_expanded);
			//get_pos_word
			if (token->str[i] != '$' && token->str[i] != ' ') //para os casos 38, 39 e 40 echo "|$USER|"
			{
				post_word = safe_substr(token->str, i, ft_strlen(token->str) - i);
				joined = safe_strjoin(joined, post_word);
			}
		}
		else if (token->str[i-1] == '$') //para os casos 5 e 6
			joined = safe_strjoin(joined, "$");
	}
	token->str = joined;
	return (token);
}