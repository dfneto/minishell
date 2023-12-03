/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:41:52 by davifern          #+#    #+#             */
/*   Updated: 2023/12/03 19:49:12 by davifern         ###   ########.fr       */
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
// cat << h1 > test > test2 < no << h2
void    execute_heredoc(t_process *first_process)
{
    t_redirect  *redirect;

    while (first_process)
    {
        redirect = first_process->redirect;
        while (redirect)
        {
            if (redirect->type == HERE_DOC)
            {
                char *input = readline(":->");
                //executo o heredoc
                while (ft_strncmp(input, redirect->name, ft_strlen(redirect->name)))
                {
                    input = readline(":->");
                }
                //vou ter que criar pipes e jogar a saida do heredoc pro pipe, creio
            }
            redirect = redirect->next;
        }
        first_process = first_process->next; 
    }
}