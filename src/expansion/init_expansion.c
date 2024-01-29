/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2024/01/29 22:09:01 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * token: it is one word of the first_token.
 * The "else if" deals with cases like: $"   t  hi   t    " 
 * or $'   t  hi   t    ' (tests 198-200) and them remove the token $
 * TODO: idealmente nesses casos (198-200) seria remover o token $ ao
 * invés de apagá-lo e seria bom ter um ponteiro previous
 */
void	check_and_expand(t_token *token, t_env env)
{
	if (ft_strchr(token->str, '$'))
		token = expand_token(token, env);
}

/*
 * For each token of the first_token it will:
 * If the token type is DOUBLE_QUOTE or STRING, 
 * check if it is expansible and expand it, 
 * otherwise does nothing.
 * first_token: is all the input text typed by the user
 */
int	expansion(t_token *first_token, t_env env)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE || first_token->type == STRING)
			check_and_expand(first_token, env);
		first_token = first_token->next;
	}
	return (0);
}
