/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 18:43:19 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	g_signal = 0;

static void	main_loop(t_env *env, t_builtin functions[]);
static void	init_minishell(t_env *env, t_builtin functions[], char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_env		env;
	t_builtin	functions[BUILTINS_NUM];

	(void)argc;
	(void)argv;
	init_minishell(&env, functions, envp);
	main_loop(&env, functions);
	clean_env(&env);
	return (0);
}

static void	init_minishell(t_env *env, t_builtin functions[], char **envp)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	init_builtins(functions);
	env->head = NULL;
	env->tail = NULL;
	env->oldpwd = NULL;
	env->pwd = NULL;
	env->last_exit = 0;
	if (create_env(env, envp))
		exit(EXIT_FAILURE);
}

static char	*get_input(int last_exit)
{
	char	*input;

	input = readline(PROMPT);
	if (input == NULL)
	{
		if (isatty(STDIN_FILENO))
			print_error("exit\n");
		exit(last_exit);
	}
	else if (input && *input)
	{
		add_history(input);
		if (check_open_quotes(input))
		{
			print_error("br.sh: parsing error - unmatched quotes\n");
			input[0] = '\0';
		}
	}
	return (input);
}

static void	main_loop(t_env *env, t_builtin functions[])
{
	char		*input;
	t_token		*first_token;
	t_process	*first_process;

	first_token = NULL;
	first_process = NULL;
	input = NULL;
	while (42)
	{
		first_token = clean_tokens(first_token);
		first_process = clean_process(first_process);
		input = clean_input(input);
		set_main_signals();
		input = get_input(env->last_exit);
		set_parent_signals();
		if (input[0] == '\0' || input[0] == '#')
			continue ;
		first_token = lexical_analysis(input, env);
		if (!first_token)
			continue ;
		first_process = process_creation(first_token, env);
		if (first_process)
			env->last_exit = execute_cmd(first_process, env, functions);
	}
	rl_clear_history();
}
