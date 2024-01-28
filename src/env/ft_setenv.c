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

static void	update_pwd_oldpwd(t_env *env, char *name, char *value)
{
	if (!ft_strcmp(name, "PWD"))
	{
		if (env->pwd)
			free(env->pwd);
		if (value)
			env->pwd = ft_strdup(value);
		else
			env->pwd = NULL;
	}
	if (!ft_strcmp(name, "OLDPWD"))
	{
		if (env->oldpwd)
			free(env->oldpwd);
		if (value)
			env->oldpwd = ft_strdup(value);
		else
			env->oldpwd = NULL;
	}
}

static int	overwrite_and_value(t_node *tmp, char *value, t_env *env)
{
	free(tmp->value);
	tmp->value = value;
	update_pwd_oldpwd(env, tmp->name, value);
	return (0);
}

static int	overwrite_and_novalue(t_node *tmp, char *value, t_env *env)
{
	tmp->value = value;
	update_pwd_oldpwd(env, tmp->name, value);
	return (0);
}

static int	no_overwrite(t_node *tmp, char *value, t_env *env)
{
	char	*current_env;

	current_env = safe_strdup(tmp->value);
	if (!current_env)
		return (1);
	if (tmp->value)
		free(tmp->value);
	tmp->value = safe_strjoin(current_env, value);
	update_pwd_oldpwd(env, tmp->name, tmp->value);
	free(current_env);
	free(value);
	return (0);
}

int	ft_setenv(t_env *env, char *name, char *value, int overwrite)
{
	t_node	*tmp;

	tmp = env->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (overwrite && tmp->value)
				return (overwrite_and_value(tmp, value, env));
			else if (overwrite)
				return (overwrite_and_novalue(tmp, value, env));
			else
				return (no_overwrite(tmp, value, env));
		}
		tmp = tmp->next;
	}
	tmp = create_node(safe_strdup(name), value);
	if (add_node_to_env(env, tmp))
		return (-1);
	return (0);
}
