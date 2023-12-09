/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:53:27 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/12/09 18:14:43 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

// static void	handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 	}
// }

// void	init_signals(void)
// {
// 	struct sigaction	act;

// 	ft_bzero(&act, sizeof(act));
// 	act.sa_handler = &handler;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }
