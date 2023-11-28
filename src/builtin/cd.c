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

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_chdir(char *str)
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
	return (0);
}

/* COLOCAR GETCWD AQUI... EM ALGUM LUGAR */

int	ft_cd(char **argv, t_env *env, int last_exit)
{
	int	argc;

	(void)last_exit;
	argc = count_args(argv);
	if (argc > 2)
	{
		print_error("Brazilian Shell: cd: too many arguments\n");
		return (1);
	}
	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "-"))
			return (ft_chdir(ft_getenv("OLDPWD", *env)));
		else if (!ft_strcmp(argv[1], "~"))
			return (ft_chdir(ft_getenv("HOME", *env)));
		else
			return (ft_chdir(argv[1]));
	}
	else
		return (ft_chdir(ft_getenv("HOME", *env)));
}
