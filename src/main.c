/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/12/10 20:10:14 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>


// void	handle_sigquit()
// {
// 	printf("control + /\n"); //nao deve printar nada, nem a barra
// }


int	main(int argc, char **argv, char **envp)
{
	// control + /
	// struct sigaction	sq;
	// sq.sa_handler = &handle_sigquit;
	// sq.sa_flags = SA_RESTART;
	// sigaction(SIGQUIT, &sq, NULL);

	t_env	env;
	

	(void)argc;
	(void)argv;
	env.head = NULL;
	env.tail = NULL;

	if (create_env(&env, envp))
		return (EXIT_FAILURE);	
	init_minishell(&env);
	clean_env(&env);
	return (0);
}
