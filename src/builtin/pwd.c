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

int	ft_pwd(char **argv, t_env *env, int last_exit)
{
	char	*directory;

	(void)argv;
	(void)last_exit;
	(void)env;
	directory = getcwd(NULL, PATH_MAX);
	if (directory)
	{
		printf("%s\n", directory);
		free(directory);
		return (EXIT_SUCCESS);
	}
	else
		return (ft_perror("pwd", NULL, 1));
}
