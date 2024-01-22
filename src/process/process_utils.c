/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:30:52 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/22 20:45:32 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

void	clean_process(t_process **process)
{
	int			i;
	t_process	*tmp;

	while (*process)
	{
		tmp = (*process)->next;
		i = 0;
		if ((*process)->cmd)
		{
			while ((*process)->cmd[i])
			{
				free((*process)->cmd[i]);
				i++;
			}
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
