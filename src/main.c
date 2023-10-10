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
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char	**env;
//	char	*str;
//	char	**or_env;

	(void)argc;
	env = create_env(envp);
	ft_env(env);
	printf("\n\n");
/* 	while (*argv != NULL)
	{
		str = expand_env(*argv, env);
		if (str != NULL)
		{
			printf("env $%s expand to %s\n", *argv, str);
			free(str);
		}
		argv++;
	} */
	ft_export(argv, env);
	char **null_char = {NULL};
	ft_export(null_char, env);
	//clean_env(&or_env);
	clean_env(&env);
	/* 		char **my_split = ft_split(argv[1], ' ');
		ft_export(my_split, &env); */
	//	printf("\n\n~~~~~~~~~~~~~~~~~~~\n\n");
	//	ft_env(env);
	/* 	init_signals();
		init_minishell(envp); */
	return (0);
}
