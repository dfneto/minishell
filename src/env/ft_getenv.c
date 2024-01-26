/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 17:23:31 by davifern         ###   ########.fr       */
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
		if (ft_strcmp(name, env.head->name) == 0)
			return (env.head->value);
		env.head = env.head->next;
	}
	return (NULL);
}
