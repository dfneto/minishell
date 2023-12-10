/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:41:52 by davifern          #+#    #+#             */
/*   Updated: 2023/12/10 19:05:34 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Para cada processo vou verificar suas redireções e caso encontre 
* um heredoc o executo a medidade que o encontro. Ex: o processo
* tem 3 redireções: <<, >, <<. Assim, executo o primeiro heredoc,
* salto o > e executo o segundo heredoc
*/
//casos guia: 
// cat << h1 >t1 | cat << h2 > t2
//casos execeção:
//TODO: cat << h1 > test > test2 < no << h2 (testar)
void    execute_heredoc(t_process *first_process)
{
    t_redirect  *redirect;
    char        *input;
    int         pipefd[2];

    input = NULL;
    while (first_process)
    {
        redirect = first_process->redirect;
        while (redirect)
        {
            if (redirect->type == HERE_DOC)
            {
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
		            exit(EXIT_FAILURE);
                }
                input = readline(":->");
                while (ft_strcmp(input, redirect->name))
                {
                    write(pipefd[1], input, ft_strlen(input));
                    write(pipefd[1], "\n", 1);
                    input = readline(":->");
                }
                close(pipefd[1]);
                first_process->infile = pipefd[0];
            }
            redirect = redirect->next;
        }
        first_process = first_process->next; 
    }
}