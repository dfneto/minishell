/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/18 18:42:16 by davifern         ###   ########.fr       */
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

# define PROMPT "\033[38;5;143mbr.sh$ \033[0;39m"
# define QUOTE_OPENED "You have to close your quotes"

# define DOUB_QUOTE_CHAR 34
# define SING_QUOTE_CHAR 39
# define SPACE_CHAR 32
# define GREATER_CHAR 62
# define LESS_CHAR 60
# define PIPE_CHAR 124

# define DOUB_QUOTE_TYPE 0
# define SING_QUOTE_TYPE 1
# define STRING_TYPE 2
# define SPACE_TYPE 3
# define OUTPUT_REDIREC_TYPE 4 // >
# define APPEND_TYPE 5 // >>
# define INPUT_REDIRECTION_TYPE 6
# define HERE_DOC_TYPE 7
# define PIPE_TYPE 8

/* TODO: acho que posso usar uma estrutura destas para tipo:
* typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;
*/

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

typedef struct s_process
{
	char				*cmd;
	char				**args;
	struct s_process	*next;
	struct s_process	*prev;
}t_process;

int			init_minishell(char **envp);
int			process_quotes(char *input);
int			clean_input(char **input);
int			is_exit(char *input);
int			expansion(t_token *first_token);
int			is_expansible(char *str);
int			get_dolar_position(char *str, int i);
int			is_expansible(char *str);
int			is_alnum_or_slash(char c);
void		add_token(t_token **first, t_token *new);
void		print_list(t_token *root);
char		*get_token_without_dolar(t_token *token);
t_token		*lexical_analysis(char *input);
t_token		*create_token(char *input, int start, int end, int type);
t_token		*get_last_token(t_token *first);
t_token		*create_tokens(char *input);
t_token		*create_token(char *input, int beginning, int end, int type);
t_token		*create_space_token(char *input, int *i);
t_token		*create_pipe_token(char *input, int *i);
t_token		*create_quote_token(char *input, int *i, int type, int quote_char);
t_token		*create_redirec_tok(char *input, int *i, int type, int quote_char);
t_token		*create_string_token(char *input, int *i);
t_process	*process_creation(t_token *first_token);
t_process	*create_process(t_token *token);

#endif
