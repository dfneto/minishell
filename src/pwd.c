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

int	ft_pwd(char **argv, char ***env, int last_exit)
{
	char	*current_dir;

	(void)argv;
	(void)env;
	(void)last_exit;
	current_dir = (char *)malloc(sizeof(char) * PATH_MAX);
	if (current_dir == NULL)
		return (-1);
	current_dir = getcwd(current_dir, PATH_MAX);
	printf("%s\n", current_dir);
	free(current_dir);
	return (0);
}
