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

static int	go_home(t_env *env)
{
	if (exist_in_env("HOME", *env) && ft_getenv("HOME", *env))
		return (ft_chdir(ft_getenv("HOME", *env), env));
	else
	{
		print_error("Brazilian Shell: cd: HOME not set\n");
		return (1);
	}
}

static int	go_oldpwd(t_env *env)
{
	int	result;

	if (exist_in_env("OLDPWD", *env))
		result = ft_chdir(ft_getenv("OLDPWD", *env), env);
	else
	{
		print_error("Brazilian Shell: cd: OLDPWD not set\n");
		return (1);
	}
	if (!result)
		printf("%s\n", ft_getenv("PWD", *env));
	return (result);
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
			return (go_oldpwd(env));
		else if (!ft_strcmp(argv[1], "~"))
			return (go_home(env));
		else if (argv[1][0] == '\0')
			result = 0;
		else
			result = ft_chdir(argv[1], env);
	}
	else
		return (go_home(env));
	return (result);
}
