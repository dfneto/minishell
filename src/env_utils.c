#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

void	clean_env(char ***env)
{
	int	i;

	if (env == NULL || *env == NULL)
	{
		return ;
	}
	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		(*env)[i] = NULL;
		i++;
	}
	free(*env);
	*env = NULL;
}

char	*expand_env(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name))
			&& env[i][ft_strlen(name)] == '=')
			return (ft_substr(env[i], ft_strchr(env[i], '=') + 1 - env[i],
					ft_strchr(env[i], '\0') - ft_strchr(env[i], '=')));
		i++;
	}
	return (ft_strdup("NOT FOUND!"));
}

void	open_space_to_insert(char ***env, int j)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	while (i > j)
	{
		(*env)[i] = (*env)[i - 1];
		i--;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

int	compare_name(char *str1, char *str2)
{
	char	*name1;
	char	*name2;
	int		ret;

	name1 = ft_substr(str1, 0, (ft_strchr(str1, '=')) - str1);
	name2 = ft_substr(str2, 0, (ft_strchr(str2, '=')) - str2);
	if (name1 == NULL || name2 == NULL)
		ft_perror(errno, "compare malloc");
	ret = ft_strcmp(name1, name2);
	free(name1);
	free(name2);
	return (ret);
}

char	**create_ordered_env(char **env)
{
	int		i;
	int		j;
	char	**or_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	or_env = (char **)malloc((i + 1) * sizeof(char *));
	if (or_env == NULL)
		ft_perror(errno, "malloc error");
	ft_memset(or_env, 0, (i + 1) * sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		j = -1;
		while (or_env[++j] != NULL)
			if (compare_name(env[i], or_env[j]) < 0)
				break ;
		open_space_to_insert(&or_env, j);
		or_env[j] = ft_strdup(env[i]);
		if (or_env[j] == NULL)
			ft_perror(errno, "malloc error");
		i++;
	}
	return (or_env);
}

char	**create_env(char **envp)
{
	char **env;
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env = (char **)malloc((i + 1) * sizeof(char *));
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