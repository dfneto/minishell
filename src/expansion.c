/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/10/14 20:39:25 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum_or_slash(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

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

int	check_and_expand(t_token **token)
{
	if (is_expansible((*token)->str))
	{
		(*token)->str = "waka";
	}
	return (1);
}

int	parameter_expansion(t_token **first_token)
{
	int	i;

	i = 0;
	while (first_token[i])
	{
		if (first_token[i]->type == 0 || first_token[i]->type == 2)
			check_and_expand(first_token);
		i++;
	}
	return (0);
}

int	expansion(t_token **first_token)
{
	parameter_expansion(first_token);
	// pathname_expansion(first_token);
	return (0);
}
