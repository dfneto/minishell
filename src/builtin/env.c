/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
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

int	ft_env(char **argv, char ***env, int last_exit)
{
	char **tmp;
	
	(void)argv;
	(void)last_exit;
	tmp = *env;
	while (**env)
	{
		if (strrchr(**env, '='))
			printf("%s\n", **env);
		(*env)++;
	}
	*env = tmp;
	return (0);
}
