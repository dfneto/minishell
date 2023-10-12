/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:23:32 by davifern          #+#    #+#             */
/*   Updated: 2023/10/12 17:55:39 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Also related to list
*/

/*
* Lesson learned: when I have an intermittent error, it means, 
* that happen sometimes and others don't, it usually is a non 
* variable declaration or bad memory allocation (cause also by typos)
* In this case sometimes I got tok->str saved and others don't.
* I was with an error with this 
*   tok = (token *)malloc(sizeof(token *)); 
* because I was allocating in memory a space for a address and 
* not for a token I like to think in the right side as allocating 
* space in memory of sizeof the type
*/
t_token	*create_token(char *input, int start, int end, int type)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = NULL;
	if (type == DOUB_QUOTE_TYPE | type == SING_QUOTE_TYPE | type == STRING_TYPE)
		tok->str = ft_substr(input, start, end - start + 1);
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

t_token	*get_last_token(t_token *first)
{
	while (first != NULL && first->next != NULL)
		first = first->next;
	return (first);
}

//TODO: simular new = NULL
void	add_token_back(t_token **first, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (*first == NULL)
		*first = new;
	else
	{
		last = get_last_token(*first);
		last->next = new;
		last = NULL;
	}
}
