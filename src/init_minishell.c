/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:18:03 by davifern          #+#    #+#             */
/*   Updated: 2024/01/16 18:56:01 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_open_fds() {
    int fd;
    for (fd = 0; fd < 10; fd++) {
        int flags = fcntl(fd, F_GETFD);
        if (flags != -1) {
            printf("File descriptor %d is open\n", fd);
            // You can add more information or actions here if needed
        }
    }
}

char	*get_input(int last_exit)
{
	char	*input;
	int		wr;

	input = readline(PROMPT);
	if (input == NULL)
	{
		if (isatty(STDIN_FILENO))
			wr = write(2, "exit\n", 6);
		(void)wr;
		exit(last_exit);
	}
	else if (input && *input)
	{
		add_history(input);
		if (check_open_quotes(input))
		{
			print_error("Brazilian Shell: parsing error - unmatched quotes\n");
			input[0] = '\0';
		}
	}
	return (input);
}

void	print_token_info(t_token *tok)
{
	if (tok)
		printf("my mem: %p\ntype>%d - str: %s\nnext: %p\n\n", tok, tok->type,
			tok->str, tok->next);
}
/*
REFACTOR
E colocar em um lugar melhor s2
*/
void	clean_tokens(t_token *first)
{
	t_token	*tmp;

	while (first)
	{
		// print_token_info(first);
		tmp = first;
		first = first->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	init_minishell(t_env *env)
{
	char		*input;
	t_token		*first_token;
	t_process	*first_process;
	t_builtin	functions[BUILTINS_NUM];

	init_builtins(functions);
	first_token = NULL;
	first_process = NULL;
	input = NULL;
	env->last_exit = 0;
	while (42)
	{
		set_main_signals();
		input = get_input(env->last_exit);
		set_parent_signals();
		if (!input)
			exit(EXIT_FAILURE);
		if (input[0] != '\0' && input[0] != '#')
		{
			first_token = lexical_analysis(input, env);
			if (first_token)
			{
				first_process = process_creation(first_token);
				if (first_process)
				{
					if (execute_heredoc(first_process))
						env->last_exit = 130;
					else if (set_redirects(first_process))
						env->last_exit = 1;
					else
						env->last_exit = execute_cmd(first_process, env, functions);
				}
			}
			else
				env->last_exit = 2;
		}
		clean_tokens(first_token);
		clean_process(&first_process);
		// limpar as redireções
		// limpar os processos
		first_token = NULL;
		clean_input(&input);
	}
	clear_history();
	// return (0);
}
