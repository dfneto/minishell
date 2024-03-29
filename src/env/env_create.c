/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 18:08:44 by davifern         ###   ########.fr       */
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

static int	set_default_envs(t_env *env, char *shlvl)
{
	int	ret;

	if (ft_setenv(env, "OLDPWD", NULL, 1))
		return (1);
	if (exists_in_env("PWD", *env) && ft_getenv("PWD", *env))
		env->pwd = safe_strdup(ft_getenv("PWD", *env));
	if (exists_in_env("OLDPWD", *env) && ft_getenv("OLDPWD", *env))
		env->oldpwd = safe_strdup(ft_getenv("OLDPWD", *env));
	if (!shlvl || shlvl[0] == '\0')
		ret = ft_setenv(env, "SHLVL", "1", 1);
	else if (shlvl[0] == '-')
		ret = ft_setenv(env, "SHLVL", "0", 1);
	else if (ft_atoi(shlvl) >= 1000)
	{
		print_error("br.sh: warning: shell level (");
		shlvl = safe_itoa(ft_atoi(shlvl) + 1);
		print_error(shlvl);
		print_error(") too high, resetting to 1\n");
		ret = ft_setenv(env, "SHLVL", "1", 1);
	}
	else
		ret = ft_setenv(env, "SHLVL",
				safe_itoa(ft_atoi(ft_getenv("SHLVL", *env)) + 1), 1);
	return (ret);
}

int	create_env(t_env *env, char **envp)
{
	int		i;
	char	*val;
	t_node	*node;
	size_t	pos;

	i = 0;
	while (envp[i] != NULL)
	{
		val = ft_strchr(envp[i], '=');
		if (val)
		{
			pos = ft_strchr(envp[i], '=') - envp[i];
			node = create_node(safe_substr(envp[i], 0, pos),
					safe_strdup(envp[i] + pos + 1));
		}
		else
			node = create_node(safe_strdup(envp[i]), NULL);
		if (add_node_to_env(env, node))
			return (1);
		i++;
	}
	if (set_default_envs(env, ft_getenv("SHLVL", *env)))
		return (1);
	return (0);
}
