/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2023/10/18 00:30:36 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum_or_slash(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_dolar_position(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}

int	get_prev_dolar_position(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}

int	is_expansible(char *str)
{
	int	i;

	i = get_dolar_position(str) + 1;
	if (is_alnum_or_slash(str[i]))
		return (1);
	return (0);
}

//TODO: tratar "  $PWD  $USER a"
/*TODO: echo "$PWD has these files that match *.txt :" *.txt
* deve gerar: echo /home/lhunath/docs has these files that 
* match *.txt : bar.txt foo.txt
*/
// char	*get_token_without_dolar(t_token *token)
// {
// 	int	i;
// 	int	start;

// 	start = get_dolar_position(token->str) + 1;
// 	i = start;
// 	while (is_alnum_or_slash(token->str[i]))
// 		i++;
// 	return (ft_substr(token->str, start, i - start));
// }

//TODO: tratar "  $PWD  $USER a" e 123$USER tem que ser 123davifern
char	*get_token_without_dolar(t_token *token)
{
	int	i;
	int	start;

	start = get_dolar_position(token->str) + 1;
	char *tmp = (char *)malloc((start + 1) * sizeof(char));
	if (!tmp)
		return NULL;
	tmp = ft_substr(token->str, 0, start - 1);

	i = start;

	while (is_alnum_or_slash(token->str[i]))
		i++;
	char *token_expansible = ft_substr(token->str, start, i - start);
	char *token_expanded = NULL;
	if (getenv(token_expansible))
	{
		token_expanded = ft_strdup(getenv(token_expansible));
	}
	char *tmp3 = ft_strjoin(tmp, token_expanded);

	start = get_dolar_position(token->str) + 1;
	tmp = (char *)malloc((start + 1) * sizeof(char));
	if (!tmp)
		return NULL;
	tmp = ft_substr(token->str, 0, start - i);

	printf("Token expandido: %s%c\n", tmp3, '!');
	token->str = tmp3;
	return tmp3;
}


void	expand(t_token *token)
{
	int		i;
	int		start;
	char	*temp;

	i = 0;
	start = 0;
	temp = NULL;
	while(token->str[i])
	{
		start = get_prev_dolar_position(token->str);
		temp = ft_substr(token->str, 0, start);
		i = start;
		while (is_alnum_or_slash(token->str[i]))
			i++;
		char *token_to_expand = ft_substr(token->str, start, i - start);
		printf("Token to expand: %s%c\n", token_to_expand, '!');
		i = 100;
	}
}