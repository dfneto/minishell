/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:23:32 by davifern          #+#    #+#             */
/*   Updated: 2023/11/21 11:59:57 by davifern         ###   ########.fr       */
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
 * str: not null when type is 0, 1 or 2
 */
t_token	*create_token(char *input, int start, int end, int type)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = NULL;
	if ((type == DOUBLE_QUOTE) | (type == SINGLE_QUOTE) | (type == STRING))
		tok->str = ft_substr(input, start, end - start + 1);
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

//TODO: juntar esse metodo com o original acima e colocar o next token como opcional ou se possível como obrigatorio
t_token	*create_token_with_next(char *input, int start, int end, int type, t_token *next_tok_after_expand)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = NULL;
	if ((type == DOUBLE_QUOTE) | (type == SINGLE_QUOTE) | (type == STRING))
		tok->str = ft_substr(input, start, end - start + 1);
	tok->type = type;
	tok->next = next_tok_after_expand;
	return (tok);
}


t_token	*get_last_token(t_token *first)
{
	while (first != NULL && first->next != NULL)
		first = first->next;
	return (first);
}

/*
 * Add the token at the end of the list of the tokens represented by first
 */
// TODO: simular new = NULL
void	add_token(t_token **first, t_token *new)
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
