/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:59:31 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/12/16 11:11:54 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_outfile(t_redirect *redirect, t_process **current)
{
	int	fd;

	if ((*current)->outfile != STDOUT_FILENO)
		close((*current)->outfile);
	if (redirect->type == APPEND)
		fd = open(redirect->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(redirect->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		ft_perror((*current)->redirect->name, NULL);
	return (fd);
}

int	get_infile(t_redirect *redirect, t_process **current)
{
	int	fd;

	if ((*current)->infile != STDIN_FILENO)
		close((*current)->infile);
	fd = open(redirect->name, O_RDONLY);
	if (fd == -1)
		ft_perror((*current)->redirect->name, NULL);
	return (fd);
}

void	get_heredoc(t_process **current)
{
	if ((*current)->infile != STDIN_FILENO)
	{
		close((*current)->infile);
		(*current)->infile = STDIN_FILENO;
	}
}

int	set_redirects(t_process *current)
{
	t_redirect	*redirect;

	while (current)
	{
		redirect = current->redirect;
		while (redirect)
		{
			if (redirect->type == APPEND
				|| redirect->type == OUTPUT_REDIRECTION)
				current->outfile = get_outfile(redirect, &current);
			else if (redirect->type == INPUT_REDIRECTION)
				current->infile = get_infile(redirect, &current);
			else if (redirect->type == HERE_DOC)
				get_heredoc(&current);
			if (current->outfile == -1 || current->infile == -1)
				break ;
			redirect = redirect->next;
		}
		if (current->heredoc && current->infile == STDIN_FILENO)
			current->infile = current->heredoc;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
