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
#include <stdio.h>
#include <unistd.h>
#include <minishell.h>

int	ft_pwd(char **argv, t_env *env, int last_exit)
{
	char	*current_dir;

	(void)argv;
	(void)last_exit;
	current_dir = ft_getenv("PWD", *env);
	printf("%s\n", current_dir);
	return (0);
}
