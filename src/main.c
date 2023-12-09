/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/12/09 21:49:18 by davifern         ###   ########.fr       */
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

// void	handle_sigint()
// {
// 	printf("control + c\n");
// }

//o control d tem funcionamento diferente se ta no meio do texto ou no inicio no caso do bash

int	main(int argc, char **argv, char **envp)
{

	// struct sigaction	sq;
	// sq.sa_handler = &handle_sigquit;
	// sq.sa_flags = SA_RESTART;
	// sigaction(SIGQUIT, &sq, NULL);

	// struct sigaction	si;
	// si.sa_handler = &handle_sigint;
	// si.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &si, NULL);

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
