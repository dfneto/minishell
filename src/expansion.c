/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/10/19 22:51:42 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expansion(t_token *token, int *i, int dolar_position)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = ft_substr(token->str,
			dolar_position + 1, *i - dolar_position - 1);
	return (getenv(word_to_expand));
}

char	*get_pre_dolar_text(t_token *token, int *dolar_position, int i)
{
	*dolar_position = get_dolar_position(token->str, i);
	return (ft_substr(token->str, i, *dolar_position - i));
}

void	expand_token(t_token *token)
{
	int		i;
	int		dolar_position;
	char	*pre_dolar;
	char	*joined;

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	while (token->str[i])
	{
		pre_dolar = get_pre_dolar_text(token, &dolar_position, i);
		joined = ft_strjoin(joined, pre_dolar);
		i = dolar_position + 1;
		if (token->str[i])
			joined = ft_strjoin(joined,
					get_word_expansion(token, &i, dolar_position));
	}
	token->str = joined;
}

//TODO: implementar
char	*get_exit_status()
{
	return ("0");
}

int	check_and_expand(t_token *token)
{
	char	*str;

	str = NULL;
	if (is_dollar_question_mark(token->str))
		token->str = get_exit_status();
	else if (is_expansible(token->str))
		expand_token(token);
	return (1);
}

int	expansion(t_token *first_token)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE
			|| first_token->type == STRING)
			check_and_expand(first_token);
		first_token = first_token->next;
	}
	return (0);
}
