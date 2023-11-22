/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:53:01 by davifern          #+#    #+#             */
/*   Updated: 2023/11/22 17:51:07 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: change this name
char	*deals_with_the_first_word(char *token_str, int i, int start, char *pre_dolar)
{
	char	*str;

	str = NULL;
	str = ft_substr(token_str, start, i - start);
	if (pre_dolar) 
		str = ft_strjoin(pre_dolar, str);
	return (str);
}

void	add_token_after(t_token **token, t_token *new_token)
{
	(*token)->next = new_token;
    (*token) = new_token;
}

t_token *set_token_str(t_token *token, char *value)
{
	token->str = ft_strdup(value);
	return token;
}

/*
* It creates a token per each word in expanded_str (it's the str expansion of the token)
//Se depois da expansão eu tenho uma palavra somente vai cair no if e sair
//se depois da expansao eu tenho várias palavras, vai cair uma vez no if e outras no else
* Return: the last part of the token expanded or the token in the 
* case that the expansion is null
* ex: a="ls   -l    -a  -F   " 
* $a patata: returns the token -F with token->next = patata
*/
t_token	*create_tok_per_word_in(char *expanded_str, char *pre_dolar, t_token *next_tok_after_expand, t_token *token)
{
	size_t			i;
	int			start;
	t_token		*new_token;
	
	i = 0;
	new_token = NULL;
	while(i < ft_strlen(expanded_str))
	{
		if (expanded_str[i] != ' ') 
		{
			start = i;
			i = ignore_spaces(expanded_str, i);
			if (!token->str) //so entra a primeira vez para cada split_token //it deals with the first word after expansion updating the str of the token
				token->str = deals_with_the_first_word(expanded_str, i, start, pre_dolar);
			else
			{
				new_token = create_token_with_next(expanded_str, start, i - 1, STRING, next_tok_after_expand);
				add_token_after(&token, new_token);
			}
		}
		i++;
	}
	return (token);
}