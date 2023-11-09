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

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_process
{
    char **cmd;
    struct s_process *next;
    struct s_process *prev;
}   t_process;

void    init_signals(void);
void    init_minishell(char ***envp);
int    execute_cmd(t_process *process, char ***envp, unsigned char last_exit);

// Process utils
t_process   *create_process(char *input);
void    clean_process(t_process **process);

// Env functions
char   **create_env(char **envp);
t_env   *create_node(char *str);
int	add_env(char *str, char ***env);
char    *expand_env(char *name, char **env, unsigned char last_exit);
void    clean_env(char ***env);
char   **create_ordered_env(char **env);

void	ft_perror(int err, char *msg);


// Built-in functions
int ft_echo(char **argv, char **env, unsigned char last_exit);
int ft_pwd(void);
int ft_exit(void);
int	ft_env(char **env);
int	ft_cd(char **argv);
int	ft_export(char **str, char ***env);
#endif
