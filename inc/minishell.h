/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/11 16:47:36 by davifern         ###   ########.fr       */
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
#define SING_QUOTE_ASCII 39
#define SPACE_ASCII 32
#define OUTPUT_REDIRECTION_ASCII 62
#define INPUT_REDIRECTION_ASCII 60
#define PIPE_ASCII 124

#define DOUB_QUOTE_TYPE 0
#define SING_QUOTE_TYPE 1
#define STRING_TYPE 2
#define SPACE_TYPE 3
#define OUTPUT_REDIRECTION_TYPE 4
#define APPEND_TYPE 5
#define INPUT_REDIRECTION_TYPE 6
#define HERE_DOC_TYPE 7
#define PIPE_TYPE 8

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
