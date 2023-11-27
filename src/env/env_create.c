/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/23 16:16:23 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

void	clean_env(t_env *env)
{
	t_node	*tmp;

	tmp = env->head;
	while (tmp)
	{
		tmp = env->head->next;
		clean_node(env->head);
		env->head = tmp;
	}
}

int	add_node_to_env(t_env *env, t_node *node)
{
	if (node == NULL)
		return (1);
	if (!env->head)
	{
		env->head = node;
		env->tail = node;
	}
	else
	{
		env->tail->next = node;
		env->tail = node;
	}
	return (0);
}

int	create_env(t_env *env, char **envp)
{
	int		i;
	t_node	*node;
	size_t	pos;

	i = 0;
	while (envp[i] != NULL)
	{
		pos = ft_strchr(envp[i], '=') - envp[i];
		node = create_node(ft_substr(envp[i], 0, pos),
				ft_strdup(envp[i] + pos + 1));
		if (add_node_to_env(env, node))
			return (1);
		i++;
	}
	if (ft_setenv(env, "OLDPWD", NULL, 1) || ft_setenv(env, "SHELL",
			ft_strdup("/home/lucas/Documents/42cursus/minishell/minishell"), 1))
		return (1);
	return (0);
}