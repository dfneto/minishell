/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/10/15 13:36:51 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum_or_slash(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

//TODO: tratar aqui o caso em que str eh $$$$$USER, por exemplo
int	is_expansible(char *str)
{
	int	case1;
	int	case2;
	
	case1 = str[0] == '$' && is_alnum_or_slash(str[1]);
	case2 = str[0] == '\"' && str[1] == '$' && is_alnum_or_slash(str[2]);
	if (case1 || case2)
		return (1);
	return (0);
}

int	check_and_expand(t_token *token)
{
	char *a;
	if (is_expansible((token)->str))
	{
		a = ft_substr((token)->str, 1, ft_strlen((token)->str) - 1);
		if (getenv(a))
			(token)->str = getenv(a);
		else
			(token)->str = a;
	}
	return (1);
}

int	parameter_expansion(t_token *first_token)
{
	while (first_token)
	{
		if (first_token->type == 0 || first_token->type == 2)
			check_and_expand(first_token);
		first_token = first_token->next;
	}
	return (0);
}

int	expansion(t_token *first_token)
{
	parameter_expansion(first_token);
	// pathname_expansion(first_token);
	return (0);
}
