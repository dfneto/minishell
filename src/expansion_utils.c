/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2023/10/15 18:01:29 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum_or_slash(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_word_start(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	while (str[i] && str[i] == '$')
		i++;
	return (i);
}

//TODO: tratar "  $PWD  $USER a"
/*TODO: echo "$PWD has these files that match *.txt :" *.txt
* deve gerar: echo /home/lhunath/docs has these files that 
* match *.txt : bar.txt foo.txt
*/
int	is_expansible(char *str)
{
	int	i;

	i = get_word_start(str);
	if (is_alnum_or_slash(str[i]))
		return (1);
	return (0);
}

char	*get_token_without_dolar(t_token *token)
{
	int	i;
	int	start;

	start = get_word_start(token->str);
	i = start;
	while (is_alnum_or_slash(token->str[i]))
		i++;
	return (ft_substr(token->str, start, i - start));
}
