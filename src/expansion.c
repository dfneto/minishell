/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/11/10 20:43:02 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = ft_substr(token->str,
			dolar_position + 1, *i - dolar_position - 1);
	printf("word to expand: %s\n", word_to_expand);
	return (getenv(word_to_expand));
}

char	*get_pre_dolar_text(t_token *token, int *dolar_position, int i)
{
	*dolar_position = get_dolar_position(token->str, i);
	return (ft_substr(token->str, i, *dolar_position - i));
}

char	*get_expanded_token(t_token *token)
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
		joined = 
		
		ft_strjoin(joined, pre_dolar);
		i = dolar_position + 1;
		if (token->str[i])
			joined = ft_strjoin(joined,
					get_word_expanded(token, &i, dolar_position));
	}
	return (joined);
}

/*
* Can expand one token into 1 or more tokens.
*/
//TODO: primeiro expandir $a=ls   -la
//TODO: expandir $b=     ls    -l    -a    -F    /
//TODO: depois expandir hola$a
//TODO: testar hola$USER$USER, hola$a
void	expand_token_int_n_tokens(t_token *token)
{
	int		i;
	int		start;
	char 	*token_str;
	t_token *aux = NULL;
	t_token *temp_last = token->next;
	t_token *new_token = NULL;

	i = 0;
	token->str++;
	token_str = ft_strdup(getenv(token->str));
	printf("token_str: %s\n", token_str);
	while(token_str[i])
	{
		if (token_str[i] != ' ')
		{
			start = i;
			while (token_str[i] && token_str[i] != ' ')
				i++;
			if (!aux)
			{
				token->str = ft_substr(token_str, start, i - start);
				aux = token;
			}
			else
			{
				new_token = create_token(token_str, start, i - 1, STRING);
				new_token->next = temp_last;
				aux->next = new_token;
				aux = new_token;
			}
		}
		i++;
	}
}

void	expand(t_token *token)
{
	if (token->type == DOUBLE_QUOTE)
		token->str = get_expanded_token(token);
	else
		expand_token_int_n_tokens(token);
}



//TODO: implementar
char	*get_exit_status()
{
	return ("0");
}

int	check_and_expand(t_token *token)
{
	if (is_dollarquestion_mark(token->str))
		token->str = get_exit_status();
	else if (is_expansible(token->str))
		expand(token);
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
