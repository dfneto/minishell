#include <minishell.h>
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include <errno.h>

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

void clean_env(char ***env)
{
    if (env == NULL || *env == NULL) {
        return;
    }

    int i = 0;
    while ((*env)[i]) {
        free((*env)[i]);
        (*env)[i] = NULL;
        i++;
    }

    free(*env);
    *env = NULL;
}


char    *expand_env(char *name, char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        if (!ft_strncmp(name, env[i], ft_strlen(name)) && env[i][ft_strlen(name)] == '=')
            return (ft_substr(env[i], ft_strchr(env[i], '=') + 1 - env[i], ft_strchr(env[i],'\0') - ft_strchr(env[i], '=')));
        i++;
    }
    return (ft_strdup("NOT FOUND!"));
}

/* char   **create_ordered_env(char **env)
{
    int i;
    int j;
    char **or_env;

    i = 0;
    while (env[i] != NULL)
        i++;
    or_env = (char **) malloc ((i + 1) * sizeof(char *));
    if (or_env == NULL)
    {
        perror("env malloc");
        exit(errno);
    }
    ft_memset(or_env, 0, (i + 1) * sizeof(char *));
    i = 0;
    while (env[i] != NULL)
    {
        j = 0;
        while (or_env[j] != NULL)
        {
            size_t size = ft_strncmp(env[i], or_env[j], ft_strlen(env[i]));
            printf("COMPARING %s AND %s - diff: %li\n", env[i], or_env[j], size);
            if (size > 0)
                j++;
            else
                break ;
        }
        while (or_env[j] != NULL)
        {
            char *tmp = or_env[j];
            or_env[j] = ft_strdup(env[i]);
            if (or_env[j] == NULL)
            {
                perror("env variable malloc");
                exit(errno);
            }
            i++;
        }

    }
    return (or_env);
} */

char   **create_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    env = (char **) malloc ((i + 1) * sizeof(char *));
    if (env == NULL)
    {
        perror("env malloc");
        exit(errno);
    }
    i = 0;
    while (envp[i] != NULL)
    {
        env[i] = ft_strdup(envp[i]);
        if (env[i] == NULL)
        {
            perror("env variable malloc");
            exit(errno);
        }
        i++;
    }
    env[i] = NULL;
    return (env);
}