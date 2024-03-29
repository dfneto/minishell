/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:27:51 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:28:06 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

static int	no_path(t_env *env, char *str)
{
	if (exists_in_env("PWD", *env))
	{
		ft_setenv(env, "PWD", safe_strdup("/"), 0);
		ft_setenv(env, "PWD", safe_strdup(str), 0);
	}
	return (ft_perror(" error retrieving current directory: \
getcwd: cannot access parent directories", "cd:", 1));
}

static void	set_env_variables(t_env *env, char *path)
{
	if (exists_in_env("OLDPWD", *env))
	{
		if (!env->pwd)
			ft_setenv(env, "OLDPWD", NULL, 1);
		else
			ft_setenv(env, "OLDPWD", safe_strdup(env->pwd), 1);
	}
	else
	{
		ft_free(env->oldpwd);
		env->oldpwd = ft_strdup(env->pwd);
	}
	if (exists_in_env("PWD", *env))
		ft_setenv(env, "PWD", safe_strdup(path), 1);
	else
	{
		ft_free(env->pwd);
		env->pwd = safe_strdup(path);
	}
	free(path);
}

int	ft_chdir(char *str, t_env *env)
{
	char		*path;

	if (chdir(str))
		return (ft_perror(str, "cd: ", 1));
	else
	{
		path = getcwd(NULL, PATH_MAX);
		if (!path)
			return (no_path(env, str));
		set_env_variables(env, path);
	}
	return (0);
}
