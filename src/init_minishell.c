/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:18:03 by davifern          #+#    #+#             */
/*   Updated: 2023/11/24 15:03:19 by davifern         ###   ########.fr       */
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
		printf("my mem: %p\ntype>%d - str: %s\nnext: %p\n\n", tok, tok->type, tok->str, tok->next);
}
/* 
REFACTOR
E colocar em um lugar melhor s2
*/
void 	clean_tokens(t_token *first)
{
	t_token *tmp;

	while (first)
	{
		//print_token_info(first);
		tmp = first;
		first = first->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);		
	}
}

void	init_minishell(t_env *envp)
{
	char		*input;
	static int	last_exit;
	t_token		*first_token;
	t_process	*first_process;
	t_builtin	functions[BUILTINS_NUM];

	(void)envp;
	init_builtins(functions);
	first_token = NULL;
	first_process = NULL;
	while (42)
	{
		input = get_input(last_exit);
		if (!input)
			exit(EXIT_FAILURE);
		if (input[0] != '\0')
		{
			first_token = lexical_analysis(input);
			//TODO: na expansao estou alterando o first_token, mas o ideal seria nao alterá-lo porque depois vai dar problema na limpeza
/* 			t_token *tmp = first_token;
			while (tmp)
			{
				print_token_info(tmp);
				tmp = tmp->next;
			} */
			expansion(first_token, last_exit);
			
			// printf("Lista de tokens finais:\n");
			// print_list(first_token);
			first_process = process_creation(first_token);
			last_exit = execute_cmd(first_process, envp, last_exit, functions);
		}
		// clean_tokens(first_token); -> POR HORA ESTA COMENTADO PORQUE TENHO QUE ALTERAR O FUNCIONAMENTO DO EXPANSION PARA NAO ALTERAR O FIRST_TOKEN
		first_token = NULL;
		clean_input(&input);
	}
	clear_history();
	// return (0);
}
