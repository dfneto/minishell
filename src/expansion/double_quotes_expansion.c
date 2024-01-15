/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2024/01/15 20:46:04 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position,
		t_env env)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (token->str[*i] && is_alpha_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = ft_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1);
	if (word_to_expand == NULL)
		return (ft_strdup(""));
	return (ft_strdup(ft_getenv(word_to_expand, env)));
}

/*
caso 1: $USER 		david - ok
caso 2: $$USER		$david - ok
caso 3: $hola				 	- ok
caso 4: $$hola		$		- ok
caso 5: $				$		- KO - now ok
caso 6: $$			$$		- KO - now ok
caso 7: echo "$/"     $/      - KO
caso 8: echo "hi$"    hi$     - ok
caso 9: echo "hi$$"   hi$$    - ok
caso 10: echo "hi$/"  hi$/    - decidi não tratar porque não encontrei a lógica. Ex: hi$/ e hi$& imprimem igual, mas hi$!, hi$(, hi$* imprime outra coisa
caso 11: echo "hi$$/"  hi$$/  - decidi não tratar porque não encontrei a lógica. Ex: hi$/ e hi$& imprimem igual, mas hi$!, hi$(, hi$* imprime outra coisa
*/
t_token	*expand_double_quote_token(t_token *token, t_env env)
{
	int i;
	int dolar_position;
	char *pre_dolar;
	char *joined;

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	while (token->str[i])
	{
		pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
		joined = ft_strjoin(joined, pre_dolar);
		i = dolar_position + 1;
		if (token->str[i])
			joined = ft_strjoin(joined, get_word_expanded(token, &i,
						dolar_position, env));
		else if (token->str[i-1] == '$') //para os casos 5 e 6
			joined = ft_strjoin(joined, "$");
		i++;
	}
	token->str = joined;
	return (token);
}