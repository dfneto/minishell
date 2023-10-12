/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/12 19:46:07 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>

# define QUOTE_OPENED "You have to close your quotes"

# define DOUB_QUOTE_ASCII 34
# define SING_QUOTE_ASCII 39
# define SPACE_ASCII 32
# define GREATER_ASCII 62
# define LESS_ASCII 60 //<
# define PIPE_ASCII 124

# define DOUB_QUOTE_TYPE 0
# define SING_QUOTE_TYPE 1
# define STRING_TYPE 2
# define SPACE_TYPE 3
# define OUTPUT_REDIRECTION_TYPE 4 // >
# define APPEND_TYPE 5 // >>
# define INPUT_REDIRECTION_TYPE 6
# define HERE_DOC_TYPE 7
# define PIPE_TYPE 8

/*
* type: 	0 " "	1 ' '	2 str	3 spc	
* 			4 >		5 >>	6 <		7 <<	
* 			8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}t_token;

int		init_minishell(char **envp);
int		process_quotes(char *input);
int		clean_input(char **input);
int		is_exit(char *input);
void	add_token_back(t_token **first, t_token *new);
void	print_list(t_token *root);
t_token	*lexical_analysis(char *input);
t_token	*create_token(char *input, int start, int end, int type);
t_token	*get_last_token(t_token *first);
t_token	*tokenization(char *input);
t_token	*create_token(char *input, int beginning, int end, int type);
t_token	*create_space_token(char *input, int *i);
t_token	*create_pipe_token(char *input, int *i);
t_token	*create_quote_token(char *input, int *i, int type, int quote_ascii);
t_token	*create_generic_token(char *input, int *i, int type, int quote_ascii);
t_token	*create_string_token(char *input, int *i);



#endif
