/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2023/11/18 13:59:09 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*expand_double_quote_token(t_token *token)
{
	int		i;
	int		dolar_position;
	char	*pre_dolar;
	char	*joined;

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
			joined = ft_strjoin(joined,
					get_word_expanded(token, &i, dolar_position));
	}
	token->str = joined;
	return (token);
}