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

void try_to_unset(char *name, char ***env)
{
	int	i;
	
	i = 0;
	while ((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		if (!ft_strncmp(name, (*env)[i], ft_strlen(name))
            && (*env)[i][ft_strlen(name)] == '=')
			{
				printf("Found: %s\n", name);
				free((*env)[i]);
				(*env)[i] = NULL;	
				i++;
				while ((*env)[i])
				{
					printf("Swapping: %s\n", (*env)[i]);

					(*env)[i - 1] = (*env)[i];
					(*env)[i] = NULL;
					i++;
				}
			}
		i++;
	}
}

int	ft_unset(char **argv, char ***env, int last_exit)
{
	(void)last_exit;
	argv++;
	while (*argv)
	{
		try_to_unset(*argv, env);
		argv++;
	}
	return (0);
}
