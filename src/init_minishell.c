/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:18:03 by davifern          #+#    #+#             */
/*   Updated: 2024/01/16 18:56:01 by davifern         ###   ########.fr       */
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

void print_open_fds() {
    int fd;
    for (fd = 0; fd < 10; fd++) {
        int flags = fcntl(fd, F_GETFD);
        if (flags != -1) {
            printf("File descriptor %d is open\n", fd);
        }
    }
}

t_token	*clean_tokens(t_token *first)
{
	t_token	*tmp;

	while (first)
	{
		// print_token_info(first);
		tmp = first;
		first = first->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	return (NULL);
}


