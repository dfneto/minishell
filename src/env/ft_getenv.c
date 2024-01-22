/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/22 16:11:24 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

int	exist_in_env(char *name, t_env env)
{
	while (env.head)
	{
		if (!ft_strcmp(name, env.head->name))
			return (1);
		env.head = env.head->next;
	}
	return (0);
}

char	*ft_getenv(char *name, t_env env)
{
	while (env.head)
	{
		if (!ft_strcmp(name, env.head->name))
			return (env.head->value);
		env.head = env.head->next;
	}
	return (NULL);
}
