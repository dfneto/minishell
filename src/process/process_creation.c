/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2023/11/27 21:28:40 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process	*get_last_process(t_process *first)
{
	while (first != NULL && first->next != NULL)
		first = first->next;
	return (first);
}

static void	add_process(t_process **first, t_process *new)
{
	t_process	*last;

	if (!new)
		return ;
	if (*first == NULL)
		*first = new;
	else
	{
		last = get_last_process(*first);
		new->prev = last;
		last->next = new;
		last = NULL;
	}
}

void	print_process(t_process *process)
{
	int	i;

	i = 0;
	printf("Process created:\n");
	while (process->cmd[i])
	{
		printf("%s\n", process->cmd[i]);
		i++;
	}
}

//TODO: diverge do bash esse caso: $"USER" ou $"dadsa"
t_process	*create_process(t_token *token, int num_cmd)
{
	t_process	*process;
	int			i;

	i = 0;
	process = (t_process *)ft_calloc(1, sizeof(t_process));
	if (process == NULL)
	{
		perror("malloc process");
		exit(EXIT_FAILURE);
	}
	process->cmd = (char **)ft_calloc(num_cmd + 1, sizeof(char *));
	if (process->cmd == NULL)
	{
		perror("malloc cmd");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		if (i == num_cmd + 1) //TODO: em que momento isso acontecerá?
		{
			perror("i == num");
			exit(EXIT_FAILURE);
		}
		if (token->str)
		{
			process->cmd[i] = ft_strjoin(process->cmd[i], token->str);
			if (process->cmd[i] == NULL)
			{
				perror("ft_strjoin");
				exit(EXIT_FAILURE);
			}
		}
		else if (token->type == PIPE)
			break ;
		else if (token->type != SPC)
		{
			token = token->next;
			while (token && !token->str)
				token = token->next;
		}
		else if (process->cmd[i] && token->type == SPC)
			i++;
		token = token->next;
	}
	//print_process(process);
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	return (process);
}

/*
* Entender o codigo do lucas
echo
echo hola
hola$a
hola$b
e"c"h'o' waka waka


echo hola | echo david


$a -> seg fault
$b

$a$a
$b$b
*/
t_process	*create_process_davis(t_token *token, int num_token_str)
{
	t_process	*process;
	int			i;

	i = 0;
	process = (t_process *)ft_calloc(1, sizeof(t_process));
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	if (process == NULL)
	{
		perror("malloc process");
		exit(EXIT_FAILURE);
	}
	process->cmd = (char **)ft_calloc(num_token_str + 1, sizeof(char *));
	if (process->cmd == NULL)
	{
		perror("malloc cmd");
		exit(EXIT_FAILURE);
	}
	while (token && i < num_token_str)
	{
		printf("token str: %s, token type: %d, i = %d\n", token->str, token->type, i);
		if (token->type == SPC)
		{
			printf("1\n");
			token = token->next;
			i++;
		}
		else if (token->str) //type STR, DOUB ou SING
		{
			printf("3\n");
			process->cmd[i] = ft_strjoin(process->cmd[i], token->str);
			token = token->next;
		}	
	}
	printf("num_tok_str: %d\n", num_token_str);
	printf("process criado: \n");
	i = 0;
	while (process->cmd[i])
		printf("<%s>", process->cmd[i++]);
	printf("\n");
	return (process);
}

t_process	*process_creation(t_token *first_token)
{
	t_process	*head;
	t_process	*process;
	t_token		*tmp;
	int			i;

	// int			outfile = STDOUT_FILENO;
	// int			infile = STDIN_FILENO;
	// char		*heredoc;
	head = NULL;
	process = NULL;
	while (first_token)
	{
		tmp = first_token;
		i = 0;
		while (first_token)
		{
			if (first_token->str)
				i++;
			/* 			if (first_token->type == OUTPUT_REDIRECTION
							|| first_token->type == APPEND)
						{
							outfile = get_outfile_fd(first_token->next,
									first_token->type);
							first_token = first_token->next;
						}
						if (first_token->type == INPUT_REDIRECTION)
						{
							infile = get_infile_fd(first_token->next);
							first_token = first_token->next;
						}
						if (first_token->type == HERE_DOC)
						{
							heredoc = get_heredoc(first_token->next);
							first_token = first_token->next;
						} */
			if (first_token->type == PIPE)
				break ;
			first_token = first_token->next;
		}
		if (i > 0)
		{
			process = create_process(tmp, i); //tmp eh o numero de token str que tenho
			add_process(&head, process);
		}
		else if (first_token)
			first_token = first_token->next;
	
	}
	return (head);
}
/* TODO:
Ver com o Lucas por que isso passa
#      |ls
Makefile                README.md               dep     
# > < | ls
Makefile                README.md               dep   

quando não deveria:
bash-3.2$ > < |ls
bash: syntax error near unexpected token `<'
bash-3.2$ > < | ls
bash: syntax error near unexpected token `<'
bash-3.2$  > < | ls
bash: syntax error near unexpected token `<'
bash-3.2$   | ls
bash: syntax error near unexpected token `|'
bash-3.2$   | ls
bash: syntax error near unexpected token `|'
*/