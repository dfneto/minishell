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

void	heredoc_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
	kill(0, SIGINT);
}

void	set_heredoc_signals(void)
{
	if (signal(SIGINT, &heredoc_ctrl_c) == SIG_ERR)
		exit(EXIT_FAILURE);
}

/* Handle signals during execution */
void	set_child_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(EXIT_FAILURE);
}
