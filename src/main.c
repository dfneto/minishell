/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/19 16:28:07 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)), char **envp)
{
	char	**env;

	//	char	*str;
	//	char	**or_env;
	(void)argc;
	(void)argv;
	env = create_env(envp);
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
	// ft_export(null_char, &env);
	// clean_env(&or_env);
	// clean_env(&env);
	/* 		char **my_split = ft_split(argv[1], ' ');
		ft_export(my_split, &env); */
	//	printf("\n\n~~~~~~~~~~~~~~~~~~~\n\n");
	//	ft_env(env);
	// init_signals();*/
	init_minishell(&env);
	return (0);
}
