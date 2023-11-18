/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:18:03 by davifern          #+#    #+#             */
/*   Updated: 2023/11/17 17:55:12 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_input(void)
{
	char		*input;

	input = readline(PROMPT);
	if (input && *input)
		add_history(input);
	return (input);
}

void	init_minishell(char ***envp)
{
	char		*input;
	static int	last_exit;
	t_token		*first_token;
	t_process	*first_process;
	t_builtin	functions[BUILTINS_NUM];

	init_builtins(functions);
	first_token = NULL;
	first_process = NULL;
	while (42)
	{
		input = get_input();
		if (!input)
			return ;
		check_open_quotes(input); //TODO: no bash se pode ter single ou double quotes abertas, e no minishell?
		first_token = lexical_analysis(input);
		expansion(first_token, last_exit);
		first_process = process_creation(first_token);
		last_exit = execute_cmd(first_process, envp, last_exit, functions);
		printf("Lista de tokens finais:\n");
		print_list(first_token);
		clean_input(&input);
	}
	clear_history();
	//return (0);
}
