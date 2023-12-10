/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:41:52 by davifern          #+#    #+#             */
/*   Updated: 2023/12/10 19:14:29 by davifern         ###   ########.fr       */
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
    char        *total_input;

    input = NULL;
    total_input = "";
    while (first_process)
    {
        redirect = first_process->redirect;
        while (redirect)
        {
            if (redirect->type == HERE_DOC)
            {
                // printf("Here doc: %s, valor:\n", redirect->name);
                input = readline(":->");
                while (ft_strcmp(input, redirect->name))
                {
                    total_input = ft_strjoin(total_input, input);
                    total_input = ft_strjoin(total_input, "\n");
                    input = readline(":->");
                }
                first_process->heredoc = ft_strdup(total_input);
                // printf("%s\n", first_process->heredoc);
            }
            redirect = redirect->next;
            total_input = "";
        }
        first_process = first_process->next; 
    }
}