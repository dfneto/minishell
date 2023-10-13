/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:18:03 by davifern          #+#    #+#             */
/*   Updated: 2023/10/13 13:42:53 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(char **envp)
{
	char	*input;
	t_token	*first_token;

	(void)envp;
	first_token = NULL;
	while (42)
	{
		input = readline("\033[38;5;143mbr.sh$ \033[0;39m");
		if (!input)
			return (0);
		if (is_exit(input))
			break ;
		process_quotes(input);
		first_token = lexical_analysis(input);
		//first_process = processos_creation(first_token);
		//execute_comand(first_process);
		print_list(first_token);
		clean_input(&input);
	}
	rl_clear_history();
	return (0);
}
