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
void    init_minishell(char **envp);
void    execute_cmd(t_process *process, char **envp);

// Process utils
t_process   *create_process(char *input);
void    clean_process(t_process *process);

// Env functions
t_env   *create_env(char **envp);
t_env   *create_node(char *str);
t_env    *add_node(t_env *node, t_env *env);


// Built-in functions
int ft_echo(char **argv);
int ft_pwd(void);
int ft_exit(void);
int	ft_env(t_env *envp);
int	ft_cd(char **argv);
int	ft_export(char **str, t_env **env);
#endif
