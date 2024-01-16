/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/23 16:17:18 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

char	**get_env_array(t_env env)
{
	char	**array;
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = env.head;
	while (tmp && ++i)
		tmp = tmp->next;
	array = (char **)safe_calloc(i + 1, sizeof(char *));
	tmp = env.head;
	while (i--)
	{
		if (tmp->value)
		{
			array[i] = safe_strjoin(tmp->name, "=");
			array[i] = safe_strjoin(array[i], tmp->value);
		}
		else
			array[i] = safe_strdup(tmp->name);
		tmp = tmp->next;
	}
	return (array);
}
