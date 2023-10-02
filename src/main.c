/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 21:05:36 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

int	main (int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		printf("Hello, Minishell!\n"); //return Error
	return (init_minishell(envp));
}
