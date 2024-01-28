/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:07 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:25:38 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

int	ft_unset(char **argv, t_env *env)
{
	argv++;
	while (*argv)
	{
		ft_unsetenv(env, *argv);
		if (!ft_strcmp(*argv, "PWD"))
		{
			free(env->pwd);
			env->pwd = NULL;
		}
		if (!ft_strcmp(*argv, "OLDPWD"))
		{
			free(env->oldpwd);
			env->oldpwd = NULL;
		}
		argv++;
	}
	return (0);
}
