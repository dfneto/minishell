/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:30:52 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:31:12 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

void	clean_process(t_process **process)
{
	int	i;

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
	free(*process);
	*process = NULL;
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
