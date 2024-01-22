/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:44:43 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 12:46:22 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	has_space(char *str)
{
	int	i;

	i = 0;
	while(str[i])
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
int	get_dolar_position(char *str, int i)
{
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}