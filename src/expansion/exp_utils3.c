/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:44:43 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 18:32:32 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_alpha_or_slash(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

/*
 * Return the dolar position or the last
 * dolar position in case of $$$, for example,
 * or \0 position, starting by i position
 * Returns -1 in case that the str hasn't $
 * and should not be expanded so.
 */
int	get_dolar_position(char *str, int start)
{
	if (str[start] == '\"')
		start++;
	while (str[start] && str[start] != '$')
		start++;
	if (str[start] == '\0')
		return (-1);
	while (str[start] && str[start] == '$')
		start++;
	return (start - 1);
}

int	is_alnum_or_slash(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}


t_token	*set_token_str(t_token *token, char *value)
{
	token->str = safe_strdup(value);
	return (token);
}