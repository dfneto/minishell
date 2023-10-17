/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:18:03 by davifern          #+#    #+#             */
/*   Updated: 2023/10/17 23:21:16 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_process *current_process, char ***envp)
{
	(void)current_process;
	(void)envp;
}

char	*get_input(void)
{
	char		*input;

	input = readline(PROMPT);
	if (input && *input)
		add_history(input);
	return (input);
}

int	init_minishell(char **envp)
{
	char		*input;
	t_token		*first_token;
	t_process	*first_process;

	first_token = NULL;
	first_process = NULL;
	while (42)
	{
		input = get_input();
		if (!input || is_exit(input))
			return (0);
		process_quotes(input);
		first_token = lexical_analysis(input);
		expansion(first_token);
		// first_process = process_creation(first_token);
		execute_cmd(first_process, &envp);
		print_list(first_token);
		clean_input(&input);
	}
	rl_clear_history();
	return (0);
}
