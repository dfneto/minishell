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
		t_env env, int last_exit)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	if (token->str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_exit));
	}
	if (token->str[*i] == ' ' || token->str[*i] == '\'')
	{
		return (ft_strdup("$"));
	}
	if (token->str[*i] == '\0')
		return (ft_strdup("$"));
	while (is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = ft_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1);
	//printf("word to expand: %s\n", word_to_expand);
	if (word_to_expand == NULL)
		return (ft_strdup(""));
	return (ft_strdup(ft_getenv(word_to_expand, env)));
}

t_token	*expand_double_quote_token(t_token *token, t_env env, int last_exit)
{
	int i;
	int dolar_position;
	char *pre_dolar;
	char *after_dolar;
	char *joined;

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	while (token->str[i])
	{
		after_dolar = ft_strchr(token->str + i, '$');
		if (!after_dolar)
			dolar_position = ft_strlen(token->str);
		else
			dolar_position = after_dolar - token->str;
		pre_dolar = ft_substr(token->str, i, dolar_position - i);
		joined = ft_strjoin(joined, pre_dolar);
		if (dolar_position != (int)ft_strlen(token->str))
		{
			i = dolar_position + 1;
			if (token->str[i])
				joined = ft_strjoin(joined, get_word_expanded(token, &i,
							dolar_position, env, last_exit));
		}
		else
			i = dolar_position;
	}
	if (joined)
		token->str = joined;
	return (token);
}