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

int	ft_pwd(char **argv, t_env *env)
{
	char	*directory;

	(void)argv;
	env->last_exit = 1;
	directory = getcwd(NULL, PATH_MAX);
	if (!directory)
	{
		env->last_exit = 0;
		directory = ft_getenv("PWD", *env);
	}
	if (!directory)
		return (EXIT_FAILURE);
	printf("%s\n", directory);
	if (env->last_exit)
		free(directory);
	return (EXIT_SUCCESS);
}
