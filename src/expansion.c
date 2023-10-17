/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/10/18 00:28:29 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_expand(t_token *token)
{
	char	*str;

	str = NULL;
	// if (is_expansible(token->str))
	// {
	// 	str = get_token_without_dolar(token);
	// 	if (getenv(str))
	// 		token->str = getenv(str);
	// }
	if (is_expansible(token->str))
		expand(token);
	return (1);
}

int	expansion(t_token *first_token)
{
	while (first_token)
	{
		if (first_token->type == DOUB_QUOTE_TYPE
			|| first_token->type == STRING_TYPE)
			check_and_expand(first_token);
		first_token = first_token->next;
	}
	return (0);
}
