/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:53:27 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/22 17:42:09 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

static void	main_control_c(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = signum;
}

/* Handle signals in main loop */
void	set_main_signals(void)
{
	if (signal(SIGINT, &main_control_c) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	set_parent_signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
