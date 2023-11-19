/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2023/11/10 20:33:51 by davifern         ###   ########.fr       */
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

t_process	*create_process(t_token *token, int num_cmd)
{
	t_process	*process;
	int			i;		

	i = 0;
	process = (t_process *) ft_calloc(1, sizeof(t_process));
	if (process == NULL)
	{
		perror("malloc process");
		exit(EXIT_FAILURE);
	}
	process->cmd = (char **) ft_calloc(num_cmd + 1, sizeof(char *));
	if (process->cmd == NULL)
	{
		perror("malloc cmd");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		if (i == num_cmd + 1)
		{
			perror("i == num");
			exit(EXIT_FAILURE);
		}
		if (token->str)
		{
			process->cmd[i] = ft_strdup(token->str);
			if (process->cmd[i] == NULL)
			{
				perror("strdup");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		else if (token->type == PIPE)
			break ;
		else if (token->type != SPC)
		{
			token = token->next;
			while (token && !token->str)
				token = token->next;
		}
		token = token->next;
	}
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
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
	//char		*heredoc;

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
/* 			if (first_token->type == OUTPUT_REDIRECTION || first_token->type == APPEND)
			{
				outfile = get_outfile_fd(first_token->next, first_token->type);
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
			process = create_process(tmp, i);
			add_process(&head, process);
		}
		else
			first_token = first_token->next;
	}
	return (head);
}
