/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2023/11/28 12:34:31 by davifern         ###   ########.fr       */
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

t_process	*create_process_L(t_token *token, int num_cmd)
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

t_process	*create_process(t_token *token, int num_token_str)
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
		if (token->str) //type STR, DOUB ou SING
		{
			process->cmd[i] = ft_strjoin(process->cmd[i], token->str);
			token = token->next;
		}	
		else if (token->type == SPC)
		{
			token = token->next;
			if (process->cmd[i])
				i++;
		}
		else if (token->type == PIPE)
			break;
	}
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
		else
			first_token = first_token->next;
	}
	return (head);
}