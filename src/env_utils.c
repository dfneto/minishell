#include <minishell.h>
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

t_env    *add_node(t_env *node, t_env *env)
{
    if (node == NULL)
        return (env);
    node->next = env;
    env = node;
    return (env);
}

t_env   *create_node(char *str)
{
    t_env   *tmp;

    tmp = (t_env *) malloc (sizeof(t_env));
    if (!tmp)
        return (NULL);
    tmp->next = NULL;
    if (strchr(str, '=') == NULL)
    {
        tmp->name = ft_substr(str, 0, ft_strchr(str, '\0') - str);
        tmp->value = NULL;
    }
    else
    {
        tmp->name = ft_substr(str, 0, ft_strchr(str, '=') - str);
        tmp->value = ft_substr(str, ft_strchr(str, '=') - str + 1, ft_strchr(str, '\0') - ft_strchr(str, '='));
    }
    return (tmp);
}

t_env   *create_env(char **envp)
{
    t_env   *head;
    t_env   *tail;
    t_env   *tmp;

    head = NULL;
    tmp = NULL;
    while (*envp)
    {
        tmp = create_node(*envp);
        if (tmp)
        {
            if (!head)
            {
                head = tmp;
                tail = tmp;
            }  
            else
            {
                tail->next = tmp;
                tail = tmp;
            }
        }
        envp++;
    }
    return (head);
}