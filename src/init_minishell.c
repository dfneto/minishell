/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:51:40 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/03 10:52:13 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

void	init_minishell(char ***envp)
{
	char		*input;
	static int	last_exit;
	t_process	*process;
	t_builtin	functions[BUILTINS_NUM];

	init_builtins(functions);
	input = NULL;
	while (1)
	{
		input = readline("Brazilian Shell ~~> ");
		if (!input)
			return ;
		if (input[0] != '\0')
		{
			add_history(input);
			process = create_process(input);
			last_exit = execute_cmd(process, envp, last_exit, functions);
			clean_process(&process);
		}
		free(input);
		input = NULL;
	}
	rl_clear_history();
}
