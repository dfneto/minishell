/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/14 11:17:22 by lsulzbac         ###   ########.fr       */
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
char **create_fucking_array(t_env env)

2. função que deleta o array (talvez não seja necessaria)
 */
int ft_unsetenv(t_env *env, char *name)
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
			if (ow)
			{
				free(tmp->value);
				tmp->value = value;
				return (0);
			}
			else
			{
				current_env = ft_strdup(tmp->value);
				free(tmp->value);
				tmp->value = ft_strjoin(current_env, value);
				free(current_env);
				if (!tmp->value)
					return (1);
			}

		}
		tmp = tmp->next;
	}
	tmp = create_node(ft_strdup(name), value);
	if (add_node_to_env(env, tmp))
		return (-1);
	return (0);
}

char	*ft_getenv(char *name, t_env env, int last_exit)
{
	if (name[0] == '?')
		return (ft_itoa(last_exit));
	while (env.head)
	{
		if (!ft_strcmp(name, env.head->name))
			return (ft_strdup(env.head->value));
		env.head = env.head->next;
	}
	return (NULL);
}