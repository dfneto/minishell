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

#include <stdio.h>
#include <libft.h>
#include <unistd.h>

int	ft_cd(char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (argv[i])
	{
		if (!ft_strncmp(argv[i], "-", 2))
		{
			chdir(getenv("OLDPWD"));
		}
		else if (chdir(argv[i]))
		{
			printf("cd: no such file or directory: %s\n", argv[1]);
			return (1);
		}
	}
	else
	{
		if (chdir(getenv("HOME")))
		{
			printf("ERROR\n");
			return (1);
		}
	}
	return (0);
}
