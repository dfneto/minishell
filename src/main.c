/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 17:19:40 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	
	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	env = create_env(envp);
	if (!env)
		exit(EXIT_FAILURE);
	else
	{
		ft_env(env);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		ft_env(env);
		exit(EXIT_SUCCESS);
	}
	init_signals();
	init_minishell(envp);
	exit(EXIT_SUCCESS);
}
