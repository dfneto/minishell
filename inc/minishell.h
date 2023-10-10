/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/10 15:55:44 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

#define DOUB_QUOTE_ASCII 34

#define DOUB_QUOTE_TYPE 0
#define SING_QUOTE_TYPE 1
#define STRING_TYPE 2

/*
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
typedef struct s_token
{
    int                 type;
    char                *str;
    struct s_token      *next;
} token;

int	    init_minishell(char **envp);
int	    process_quotes(char *input);
int     clean_input(char **input);
int     is_exit(char *input);
token   *tokenization(char *input);
token   *create_token(char *input, int beginning, int end, int type);

#endif
