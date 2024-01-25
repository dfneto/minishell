/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:41:52 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 17:53:32 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_parent_heredoc(int pipefd[2])
{
	int	child_exit;

	close(pipefd[1]);
	wait(&child_exit);
	if (WIFEXITED(child_exit))
		return (pipefd[0]);
	close(pipefd[0]);
	return (-1);
}

static void	do_child_heredoc(int pipefd[2], char *name)
{
	char	*input;

	set_heredoc_signals();
	close(pipefd[0]);
	input = readline(":->");
	if (input)
	{
		while (ft_strcmp(input, name))
		{
			write(pipefd[1], input, ft_strlen(input));
			write(pipefd[1], "\n", 1);
			free(input);
			input = readline(":->");
			if (!input)
				break ;
		}
		free(input);
	}
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

static int	do_heredoc_fork(t_process *first_process, t_redirect *redirect)
{
	int	pipefd[2];
	int	id;

	if (first_process->heredoc)
		close(first_process->heredoc);
	if (pipe(pipefd) == -1)
		exit(ft_perror("pipe", NULL, 1));
	id = fork();
	if (id < 0)
		exit(ft_perror("fork", NULL, 1));
	if (id == CHILD)
		do_child_heredoc(pipefd, redirect->name);
	else
		first_process->heredoc = do_parent_heredoc(pipefd);
	if (first_process->heredoc < 0)
		return (1);
	return (0);
}

/*
 * Para cada processo vou verificar suas redireções e caso encontre
 * um heredoc o executo a medidade que o encontro. Ex: o processo
 * tem 3 redireções: <<, >, <<. Assim, executo o primeiro heredoc,
 * salto o > e executo o segundo heredoc
 */
// casos guia:
// cat << h1 >t1 | cat << h2 > t2
// casos execeção:
// TODO: cat << h1 > test > test2 < no << h2 (testar)

int	execute_heredoc(t_process *first_process)
{
	t_redirect	*redirect;

	while (first_process)
	{
		redirect = first_process->redirect;
		while (redirect)
		{
			if (redirect->type == HERE_DOC)
			{
				if (do_heredoc_fork(first_process, redirect))
					return (1);
			}
			redirect = redirect->next;
		}
		first_process = first_process->next;
	}
	return (0);
}
