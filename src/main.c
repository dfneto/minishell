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
#include <libft.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	
	(void)argc;
	env = create_env(envp);
	if (!env)
		exit(EXIT_FAILURE);
	else if (argc > 1)
	{
		ft_env(env);
		char **my_split = ft_split(argv[1], ' ');
		ft_export(my_split, &env);
		printf("~~~~~~~~~~~~~~~~~~~\n");
		ft_env(env);
		exit(EXIT_SUCCESS);
	}
/* 	init_signals();
	init_minishell(envp); */
	exit(EXIT_SUCCESS);
}
