/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2023/11/22 12:33:57 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position,
		t_env env)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = safe_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1);
	return (safe_strdup(ft_getenv(word_to_expand, env)));
}

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
		joined = safe_strjoin(joined, pre_dolar);
		i = dolar_position + 1;
		if (token->str[i])
			joined = safe_strjoin(joined, get_word_expanded(token, &i,
						dolar_position, env));
	}
	token->str = joined;
	return (token);
}