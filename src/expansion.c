/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/10/18 18:51:35 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expansion(t_token *token, int *i, int dolar_position)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (is_alnum_or_slash(token->str[*i]))
				(*i)++;
	word_to_expand = ft_substr(token->str, dolar_position + 1, *i - dolar_position - 1);
	return (getenv(word_to_expand));
}

void	expand_token(t_token *token)
{
	int		i;
	int		dolar_position;
	char	*temp;
	char	*env_to_expand;
	char	*env_expanded;
	char	*joined;
	
	i = 0;
	dolar_position = 0;
	temp = NULL;
	env_to_expand = NULL;
	env_expanded = NULL;
	joined = NULL;
	while(token->str[i])
	{
		//pre expand text
		dolar_position = get_dolar_position(token->str, i);
		temp = ft_substr(token->str, i, dolar_position - i);
		joined = ft_strjoin(joined, temp);

		i = dolar_position + 1;
		if (token->str[i])
		{
			while (is_alnum_or_slash(token->str[i]))
				i++;
			env_to_expand = ft_substr(token->str, dolar_position + 1, i - dolar_position - 1);
			env_expanded = getenv(env_to_expand);
			joined = ft_strjoin(joined,
				env_expanded);
			// joined = ft_strjoin(joined,
			// 	get_word_expansion(token, &i, dolar_position));
		}
	}
	token->str = joined;
}

int	check_and_expand(t_token *token)
{
	char	*str;

	str = NULL;
	if (is_expansible(token->str))
		expand_token(token);
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
