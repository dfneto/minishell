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

/* static void	no_pwd(t_env *env, char *oldpwd)
{
	if (exist_in_env("OLDPWD", *env))
	{
		if (oldpwd_static)
			ft_setenv(env, "OLDPWD", safe_strdup(oldpwd), 1);
		else
			ft_setenv(env, "OLDPWD", NULL, 1);
		oldpwd_static = safe_strdup(oldpwd);
	}
	ft_free(env->oldpwd);
	env->oldpwd = safe_strdup(pwd);
	ft_free(env->pwd);
	env->pwd = safe_strdup(path);
} */

static void	yes_pwd(t_env *env, char *path)
{
	if (exists_in_env("OLDPWD", *env))
	{
		if (!env->pwd)
			ft_setenv(env, "OLDPWD", NULL, 1);
		else
			ft_setenv(env, "OLDPWD", safe_strdup(env->pwd), 1);
	}
	ft_free(env->oldpwd);
	env->oldpwd = env->pwd;
	if (exists_in_env("PWD", *env))
		ft_setenv(env, "PWD", path, 1);
	env->pwd = safe_strdup(path);
}

int	ft_chdir(char *str, t_env *env)
{
	char		*path;
/* 	char		*oldpwd;

	oldpwd = getcwd(NULL, PATH_MAX); */

	if (chdir(str))
	{
/* 		if (oldpwd)
			free(oldpwd); */
		return (ft_perror(str, "cd: ", 1));
	}
	else
	{
		path = getcwd(NULL, PATH_MAX);
		if (!path)
			return (no_path(env, str));
		//if (exist_in_env("PWD", *env))
		yes_pwd(env, path);
/* 		else
			no_pwd(env, oldpwd); */
/* 		if (oldpwd)
			free(oldpwd); */
	}
	return (0);
}
