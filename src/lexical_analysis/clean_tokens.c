/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:26:39 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/25 11:26:40 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*clean_tokens(t_token *first)
{
	t_token	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	return (NULL);
}
