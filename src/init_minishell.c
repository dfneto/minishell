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
#include <fcntl.h>

void	init_minishell(char ***envp)
{
	char		*input;
	static int	last_exit;
	// int			outfile;
	t_process	*process;
	t_builtin	functions[BUILTINS_NUM];

	//outfile = open("test.log", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);

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
			process = create_process(input, STDIN_FILENO, STDOUT_FILENO);
			last_exit = execute_cmd(process, envp, last_exit, functions);
			clean_process(&process);
		}
		free(input);
		input = NULL;
	}
	rl_clear_history();
}
