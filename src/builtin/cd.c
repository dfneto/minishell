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

#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	ft_chdir(char *str, t_env *env)
{
	if (chdir(str))
	{
		if (errno == EACCES)
		{
			print_error("Brazilian Shell: cd: ");
			print_error(str);
			print_error(": Permission denied\n");
		}
		else if (errno == ENAMETOOLONG)
		{
			print_error("Brazilian Shell: cd: ");
			print_error(str);
			print_error(": File name too long\n");
		}
		else if (errno == ENOTDIR)
		{
			print_error("Brazilian Shell: cd: ");
			print_error(str);
			print_error(": Not a directory\n");
		}
		else
		{
			print_error("Brazilian Shell: cd: ");
			print_error(str);
			print_error(": No such file or directory\n");
		}
		return (1);
	}
	else
	{
		char *path = (char *) ft_calloc(PATH_MAX, sizeof(char));
		path = getcwd(path, PATH_MAX);
		char *pwd = ft_getenv("PWD", *env);
		if (pwd == NULL)
			ft_setenv(env, "OLDPWD",  NULL, 1);
		else
			ft_setenv(env, "OLDPWD", ft_strdup(ft_getenv("PWD", *env)), 1);
		ft_setenv(env, "PWD", path, 1);
	}
	return (0);
}

/*
COLOCAR GETCWD AQUI... EM ALGUM LUGAR 
 REFACTOR TUDO
 VERIFICAR TROCA DE ENV -> PWD & OLDPWD
 */

int	ft_cd(char **argv, t_env *env, int last_exit)
{
	int	result;

	(void)last_exit;
	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "-"))
		{
			result = ft_chdir(ft_getenv("OLDPWD", *env), env);
			if (!result)
				printf("%s\n", ft_getenv("PWD", *env));
		}
		else if (!ft_strcmp(argv[1], "~"))
			result = ft_chdir(ft_getenv("HOME", *env), env);
		else if (argv[1][0] == '\0')
			result = 0;
		else
			result = ft_chdir(argv[1], env);
	}
	else
		return (ft_chdir(ft_getenv("HOME", *env), env));
	if (result && argv[2])
		print_error("Brazilian Shell: cd: too many arguments\n");
	return (result);
}
