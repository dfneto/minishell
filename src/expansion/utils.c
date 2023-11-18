/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2023/11/10 20:58:40 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum_or_slash(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/*
* Return the dolar position or /0 position
*/
int	get_dolar_position(char *str, int i)
{
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (i);
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}

int	is_expansible(char *str)
{
	int	i;

	i = get_dolar_position(str, 0) + 1;
	if (is_alnum_or_slash(str[i]))
		return (1);
	return (0);
}

int	is_dollarquestion_mark(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (0);
}

void	remove_spaces(char **str)
{
	//fazer um ft_strtrim para quitar los espacios de principio y del final. ex: _____hola_julia____ -> hola_julia
	int	i;

	i = 0;
	while (str[i])
	{

	}
}