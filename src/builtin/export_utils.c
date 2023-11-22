/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:16:59 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/14 11:17:01 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

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
	or_env = (char **)ft_calloc((i + 1), sizeof(char *));
	if (or_env == NULL)
		ft_perror(errno, "malloc error");
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
