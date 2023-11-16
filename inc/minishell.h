/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:14:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 17:14:07 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROGRAM_NAME "Brazilian Shell ~~> "
# define CHILD 0
# define BUILTINS_NUM 7

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_process
{
    int  index;
    char **cmd;
    int fd[2];
    struct s_process *next;
    struct s_process *prev;
    int infile;
    int outfile;
}   t_process;

typedef struct s_builtin
{
    char    *name;
    int     (*function)(char **, char ***, int);
}   t_builtin;

void    init_signals(void);
void    init_minishell(char ***envp);
int    execute_cmd(t_process *process, char ***envp, int last_exit, t_builtin funcitons[]);

// Process utils
t_process   *create_process(char *input, int in, int out);
void    clean_process(t_process **process);

// Env functions
char   **create_env(char **envp);
t_env   *create_node(char *str);
int	add_env(char *str, char ***env);
char    *expand_env(char *name, char **env, int last_exit);
void    clean_env(char ***env);
char   **create_ordered_env(char **env);

void	ft_perror(int err, char *msg);

//Init builtins
void	init_builtins(t_builtin array[]);

int	execute_builtins(char **argv, char ***env, int last_exit, t_builtin functions[]);

int	ft_strcmp(char *str1, char *str2);
int print_error(char *str);


// Built-in functions
int ft_echo(char **argv, char ***env, int last_exit);
int ft_pwd(char **argv, char ***env, int last_exit);
int ft_exit(char **argv, char ***env, int last_exit);
int	ft_env(char **argv, char ***env, int last_exit);
int	ft_cd(char **argv, char ***env, int last_exit);
int	ft_export(char **argv, char ***env, int last_exit);
int	ft_unset(char **argv, char ***env, int last_exit);

#endif
