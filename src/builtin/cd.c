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

int	ft_chdir(char *str, t_env *env)
{
	char	*path;
	char	*pwd;

	if (chdir(str))
	{
		ft_perror(str, "cd: ");
		return (1);
	}
	else
	{
		path = getcwd(NULL, PATH_MAX);
		pwd = ft_getenv("PWD", *env);
		if (pwd == NULL)
			ft_setenv(env, "OLDPWD", NULL, 1);
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
	return (result);
}
