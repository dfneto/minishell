/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:17:20 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/14 11:17:22 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*expand_env(char *name, char **env, unsigned char last_exit)
{
	int	i;

	i = 0;
	name++;
	if (name[0] == '?')
		return (ft_itoa(last_exit));
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

char	**create_env(char **envp)
{
	char	**env;
	int		i;

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
