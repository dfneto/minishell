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
	if (exist_in_env("PWD", *env))
	{
		ft_setenv(env, "PWD", "/", 0);
		ft_setenv(env, "PWD", str, 0);
	}
	return (ft_perror(" error retrieving current directory: \
			getcwd: cannot access parent directories", "cd:", 1));
}

static void	no_pwd(t_env *env, char *oldpwd, char **oldpwd_static)
{
	if (exist_in_env("OLDPWD", *env))
	{
		if ((*oldpwd_static))
			ft_setenv(env, "OLDPWD", oldpwd, 1);
		else
			ft_setenv(env, "OLDPWD", NULL, 1);
		(*oldpwd_static) = ft_strdup(oldpwd);
	}
}

static void	yes_pwd(t_env *env, char *path)
{
	char	*pwd;

	pwd = ft_getenv("PWD", *env);
	if (exist_in_env("OLDPWD", *env))
	{
		if (pwd == NULL)
			ft_setenv(env, "OLDPWD", NULL, 1);
		else
			ft_setenv(env, "OLDPWD", ft_strdup(pwd), 1);
	}
	ft_setenv(env, "PWD", path, 1);
}

int	ft_chdir(char *str, t_env *env)
{
	char		*path;
	char		*oldpwd;
	static char	*oldpwd_static;

	oldpwd = getcwd(NULL, PATH_MAX);
	if (chdir(str))
		return (ft_perror(str, "cd: ", 1));
	else
	{
		path = getcwd(NULL, PATH_MAX);
		if (!path)
			return (no_path(env, str));
		if (exist_in_env("PWD", *env))
			yes_pwd(env, path);
		else
			no_pwd(env, oldpwd, &oldpwd_static);
	}
	return (0);
}
