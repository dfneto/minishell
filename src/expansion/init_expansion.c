/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/11/22 15:28:54 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*expand(t_token *token, int last_exit, t_env env)
{
	if (!ft_strchr(token->str, '$'))
		return (token);
	return (expand_double_quote_token(token, env, last_exit));
}
/*
 * Expand al the tokens of type DOUBLE_QUOTE or STRING
 */
int	expansion(t_token *first_token, int last_exit, t_env env)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE || first_token->type == STRING)
			expand(first_token, last_exit, env);
		first_token = first_token->next;
	}
	return (0);
}
