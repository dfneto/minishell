/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/21 21:37:36 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define PROMPT "\r\033[38;5;143mbr.sh$ \033[0;39m"
# define QUOTE_OPENED "You have to close your quotes"

# define CHILD 0
# define BUILTINS_NUM 7

# define DOUB_QUOTE_CHAR 34
# define SING_QUOTE_CHAR 39
# define SPACE_CHAR 32
# define GREATER_CHAR 62
# define LESS_CHAR 60
# define PIPE_CHAR 124

# define L_MAX "9223372036854775807"
# define L_MIN "9223372036854775808"

extern int g_signal;


// typedef enum char //usar isso ou os defines?
// {
// 	,
// 	GREAT,
// 	GREAT_GREAT,
// 	LESS,
// 	LESS_LESS,
// }	t_char;

// # define DOUB_QUOTE_TYPE 0
// # define SING_QUOTE_TYPE 1
// # define STRING_TYPE 2
// # define SPACE_TYPE 3
// # define OUTPUT_REDIREC_TYPE 4 // >
// # define APPEND_TYPE 5 // >>
// # define INPUT_REDIRECTION_TYPE 6
// # define HERE_DOC_TYPE 7

typedef enum token_type
{
	DOUBLE_QUOTE = 0,
	SINGLE_QUOTE = 1,
	STRING = 2,
	SPC = 3,
	OUTPUT_REDIRECTION = 4,
	APPEND = 5,
	INPUT_REDIRECTION = 6,
	HERE_DOC = 7,
	PIPE = 8,
	NL = 9
}						t_type;

/*
 * type: 	0 " "	1 ' '	2 str	3 spc
 * 			4 >		5 >>	6 <		7 <<
 * 			8 |
 * str: not null when type is 0, 1 or 2
 */
typedef struct s_token
{
	int					type;
	char				*str;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	t_type				type;
	char				*name;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_process
{
	char				**cmd;
	int					fd[2];
	struct s_process	*next;
	struct s_process	*prev;
	int					infile;
	int					outfile;
	int					heredoc;
	struct s_redirect	*redirect;
}						t_process;

typedef struct s_node
{
	char				*name;
	char				*value;
	struct s_node		*next;
}						t_node;

typedef struct s_env
{
	t_node				*head;
	t_node				*tail;
	int					last_exit;
}						t_env;

typedef struct s_builtin
{
	char				*name;
	int					(*function)(char **, t_env *);
}						t_builtin;

int						check_open_quotes(char *input);
int						clean_input(char **input);
int						is_exit(char *input);
int						expansion(t_token *first_token, 
							t_env env);
int						get_dolar_position(char *str, int i);
int						is_expansible(char *str);
int						is_alnum_or_slash(char c);
int						is_dollarquestion_mark(char *str);
void					add_token(t_token **first, t_token *new);
void					add_redirect(t_redirect **first, t_redirect *new);
void					print_token(t_token *token);
void					print_list_token(t_token *root);
void					print_list_redirect(t_redirect *redirect);
void					print_list_process(t_process *process);
void					print_process(t_process *root);
void					remove_spaces(char **str);
int					execute_heredoc(t_process *first_process);
char					*remove_pre_dolar_text(char *str, int start);
void					add_token_after(t_token **token, t_token *new_token);
char					*get_token_without_dolar(t_token *token);
char					*g_pre_dol(char *str, int *dolar_position,
							int i);
char					*deals_with_the_first_word(char *token_str, int i,
							int start, char *pre_dolar);
t_token					*set_token_str(t_token *token, char *value);
t_token					*create_tok_per_word_in(char *expanded_str, t_token *next_tok_after_expand, t_token *token);
char					*get_exit_status(int last_exit);
t_token					*create_token_split(char *str, t_token *next_token);
t_token					*expand_token_int_n_tokens(t_token *token, t_env env);
t_token					*expand_double_quote_token(t_token *token, t_env env);
t_token					*lexical_analysis(char *input);
t_token					*create_token(char *input, int start, int end,
							int type);
t_token					*get_last_token(t_token *first);
t_token					*create_tokens(char *input);
t_token					*create_token(char *input, int beginning, int end,
							int type);
t_token					*create_space_token(char *input, int *i);
t_token					*create_pipe_token(char *input, int *i);
t_token					*create_quote_token(char *input, int *i, int type,
							int quote_char);
t_token					*create_redirec_tok(char *input, int *i, int type,
							int quote_char);
t_token					*create_string_token(char *input, int *i);
t_process				*process_creation(t_token *first_token);
t_process				*create_process(t_token *token, int i);
t_redirect				*create_redirect(char *name, t_type type);

// VVVVVV LUKITAS VVVVV
//Organizei as funções por "modulo", cada módulo corresponde ao nome do
//folder. Dentro de cada "módulo" separei as funções por funcionalidades.
//Cada módulo começa com o nome todo em maiuscula e comentado como multilinha.
//Cada funcionalidade tem o nome apenas com as primeiras letras em maiuscula 
// e comentado com

/* EXECUTION */
// Execute CMD
int						execute_cmd(t_process *process, t_env *envp,
							 t_builtin funcitons[]);

// Single cmd
int						execute_single_cmd(t_process *process, t_env *env,
							 t_builtin functions[]);

// Single cmd utils
int						do_single_fork(char *path, char **cmd, t_env env);
void					set_single_redirects(t_process *process, int *og_stdin,
							int *og_stdout);
void					reset_redirects(t_process *process, int *og_stdin,
							int *og_stdout);

// Mult cmds
int						execute_multi_cmd(t_process *process, t_env *env,
							 t_builtin functions[]);

// Mult cmds utils
int						main_execution(t_process *process, t_env *env,
							int num_arr[3], t_builtin functions[]);
int						count_processes(t_process *process);

// Execute Utils
char					*get_path(char **cmd, t_env env);
void					close_pipes(int pipe[]);

/* ENV */
// Env Creation/Cleaning Functions
int						create_env(t_env *env, char **envp);
int						add_node_to_env(t_env *env, t_node *node);
void					clean_env(t_env *env);

// Env Utils Functions
int						exist_in_env(char *name, t_env env);
int						ft_setenv(t_env *env, char *name, char *value, int ow);
int						ft_unsetenv(t_env *env, char *name);
char					*ft_getenv(char *name, t_env env);
char					**get_env_array(t_env env);

// Node Functions
void					clean_node(t_node *node);
t_node					*create_node(char *name, char *value);

/* UTILS */
int						ft_strcmp(char *str1, char *str2);
int						print_error(char *str);
int						print_cmd_not_found(char *cmd);
char					*ft_strtok(char *input, const char *delim);
int						ft_perror(char *msg, char *func_name, int exit_status);

// Safe allocation functions
void					*safe_malloc(size_t len);
char					*safe_itoa(int n);
char					*safe_strdup(const char *s1);
void					*safe_calloc(size_t count, size_t size);
char					**safe_split(char const *s, char c);
char					*safe_strjoin(char const *s1, char const *s2);
char					*safe_strtrim(char const *s1, char const *set);
char					*safe_substr(char const *s, unsigned int start, size_t len);

/* BUILTINS */
// Init builtins
void					init_builtins(t_builtin array[]);
int						is_builtins(char **argv, t_builtin functions[]);
int						execute_builtins(char **argv, t_env *env, 
							t_builtin functions[]);

// Built-in functions
int						ft_echo(char **argv, t_env *env);
int						ft_pwd(char **argv, t_env *env);
int						ft_exit(char **argv, t_env *env);
int						ft_env(char **argv, t_env *env);
int						ft_cd(char **argv, t_env *env);
int						ft_export(char **argv, t_env *env);
int						ft_unset(char **argv, t_env *env);

// ft_export utils
int						print_ordered(t_env env);

// ft_cd utils
int						ft_chdir(char *str, t_env *env);

/* SIGNALS */
void	set_main_signals(void);
void set_child_signals(void);
void set_parent_signals(void);

// VVVVVVVVVVVVV Nao organizado VVVVVVV

// Process utils
// t_process   *create_process(char *input, int in, int out);
void					clean_process(t_process **process);
void					init_signals(void);
void					init_minishell(t_env *envp);

int						validate_tokens(t_token *token);

int						set_redirects(t_process *process);

#endif
