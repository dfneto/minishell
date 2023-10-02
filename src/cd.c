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
#include <stdio.h>
#include <unistd.h>

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
		printf("cd: no such file or directory: %s\n", str);
		return (1);
	}
	return (0);
}

int	ft_cd(char **argv)
{
	int	argc;

	argc = count_args(argv);
	if (argc > 2)
	{
		printf("Brazilian Shell: cd: too many arguments\n");
		return (1);
	}
	if (argv[1])
	{
		if (!ft_strncmp(argv[1], "-", 2))
			return (ft_chdir(getenv("OLDPWD")));
		else
			return (ft_chdir(argv[1]));
	}
	else
		return (ft_chdir(getenv("HOME")));
}
