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

/*
TODO:
1. função que transforma lista em char **
char	**create_fucking_array(t_env env)

2. função que deleta o array (talvez não seja necessaria)
 */
char	**get_env_array(t_env env)
{
	char	**array;
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = env.head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = env.head;
	while (i--)
	{
		if (tmp->value)
		{
			array[i] = ft_strjoin(tmp->name, "=");
			array[i] = ft_strjoin(array[i], tmp->value);
		}
		else
			array[i] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	return (array);
}

int	ft_unsetenv(t_env *env, char *name)
{
	t_node	*tmp;
	t_node	*prev;

	if (name == NULL)
		return (1);
	tmp = env->head;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (!prev)
				env->head = tmp->next;
			else
				prev->next = tmp->next;
			clean_node(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

/*
REFACTOR IT
*/
int	ft_setenv(t_env *env, char *name, char *value, int ow)
{
	t_node	*tmp;
	char	*current_env;

	if (!value && !ow)
		return (0);
	tmp = env->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (ow && tmp->value)
			{
				free(tmp->value);
				tmp->value = value;
				return (0);
			}
			else if (ow)
			{
				tmp->value = value;
				return (0);
			}
			else
			{
				current_env = ft_strdup(tmp->value);
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strjoin(current_env, value);
				free(current_env);
				if (!tmp->value)
					return (1);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	tmp = create_node(ft_strdup(name), value);
	if (add_node_to_env(env, tmp))
		return (-1);
	return (0);
}

char	*ft_getenv(char *name, t_env env)
{
	while (env.head)
	{
		if (!ft_strcmp(name, env.head->name))
			return (env.head->value);
		env.head = env.head->next;
	}
	return (NULL);
}
