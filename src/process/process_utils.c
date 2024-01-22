/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:30:52 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/30 23:45:56 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

void	clean_process(t_process **process)
{
	int	i;
	t_process *tmp;
	
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
*/
void	add_redirect(t_redirect **first, t_redirect *new) //TODO: experimentar com * porque no void    execute_heredoc(t_process *first_process) eu usei um * somente
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

/* t_process	*create_process(char *input, int in, int out)
{
	t_process	*tmp;
	t_process	*head;
	t_process	*tail;
	char		**process_str;
	int			i;

	process_str = ft_split(input, '|');
	if (process_str == NULL)
		exit(1);
	i = 0;
	head = NULL;
	while (process_str[i])
	{
		tmp = (t_process *)malloc(sizeof(t_process));
		if (tmp == NULL)
			exit(1);
		tmp->cmd = ft_split(process_str[i], ' ');
		if (tmp->cmd == NULL)
		{
			free(tmp);
			exit(1);
		}
		tmp->index = i;
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->infile = in;
		tmp->outfile = out;
		if (!head)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			tail->next = tmp;
			tmp->prev = tail;
			tail = tmp;
		}
		i++;
	}
	tmp = NULL;
	tail = NULL;
	free(process_str);
	process_str = NULL;
	return (head);
} */
