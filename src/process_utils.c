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
#include <stdlib.h>

void	clean_process(t_process *process)
{
	int	i;

	i = 0;
	if (process->cmd)
	{
		while (process->cmd[i])
		{
			free(process->cmd[i]);
			i++;
		}
		free(process->cmd);
	}
	free(process);
	process = NULL;
}

t_process	*create_process(char *input)
{
	t_process	*tmp;

	tmp = (t_process *)malloc(sizeof(t_process));
	if (tmp == NULL)
		return (NULL);
	tmp->cmd = ft_split(input, ' ');
	if (tmp->cmd == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
