/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:30:52 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/23 17:18:03 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

t_process	*clean_process(t_process **process)
{
	int			i;
	t_process	*tmp;

	while (*process)
	{
		tmp = (*process)->next;
		i = -1;
		if ((*process)->cmd)
		{
			while ((*process)->cmd[++i])
				free((*process)->cmd[i]);
			free((*process)->cmd);
		}
		if ((*process)->infile != STDIN_FILENO)
			close((*process)->infile);
		if ((*process)->outfile != STDOUT_FILENO)
			close((*process)->outfile);
		if ((*process)->redirect)
			clean_redirects((*process)->redirect);
		free(*process);
		*process = tmp;
	}
	return (NULL);
}

/*
* Resolvi fazer esse add ponteiro de forma diferente para treinar 
* o uso de **
* TODO: experimentar com * porque no 
* void    execute_heredoc(t_process *first_process) eu usei um * somente
*/
void	add_redirect(t_redirect **first, t_redirect *new)
{
	t_redirect	*temp;

	if (!new)
		return ;
	if (*first == NULL)
		*first = new;
	else
	{
		temp = (*first);
		while (temp != NULL && temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_process	*get_last_process(t_process *first)
{
	while (first != NULL && first->next != NULL)
		first = first->next;
	return (first);
}

void	add_process(t_process **first, t_process *new)
{
	t_process	*last;

	if (!new)
		return ;
	if (*first == NULL)
		*first = new;
	else
	{
		last = get_last_process(*first);
		new->prev = last;
		last->next = new;
		last = NULL;
	}
}

/*
* Returns the numbers of tokens that have something in str 
* (DOUBLE, SINGLE QUOTE and STR tokens) and before a PIPE
* in the case that has one
*/
int	look_for_commands(t_token **head)
{
	int		num_tok_str;

	num_tok_str = 0;
	while (*head)
	{
		if ((*head)->str)
			num_tok_str++;
		else if ((*head)->type == PIPE)
		{
			*head = (*head)->next;
			break ;
		}
		else if ((*head)->type != SPC)
		{
			while (*head && !(*head)->str)
				*head = (*head)->next;
		}
		*head = (*head)->next;
	}
	return (num_tok_str);
}
