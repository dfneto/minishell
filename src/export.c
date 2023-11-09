/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:07 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:25:38 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

static void	print_ordered(char **env)
{
	char	**ordered;
	int		i;

	printf("print_ordered\n");
	ordered = create_ordered_env(env);
	if (ordered == NULL)
		return ;
	i = 0;
	while (ordered[i] != NULL)
	{
		printf("declare -x %s\n", ordered[i]);
		i++;
	}
	clean_env(&ordered);
}

static int	is_valid_env(char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (0);
	str++;
	while (*str && *str != '=' && *str != '+')
	{
		if(!ft_isalnum(*str))
			return (0);
		str++;
	}
	if (*str == '+')
	{
		str++;
		if (*str != '=')
			return (0);
	}
	return (1);
}

int	add_env(char *str, char ***env)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new_env = (char **) malloc (sizeof(char *) * (i + 2));
	if (new_env == NULL)
	{
		//error
		return (1);
	}
	else
	{
		ft_memset(new_env, 0, sizeof(char *) * (i + 2));
		i = 0;
		while ((*env)[i] != NULL)
		{
			new_env[i] = (*env)[i];
			i++;
		}
		new_env[i] = ft_strdup(str);
		free(*env);
		*env = new_env;
	}
	return (0);
}

int	ft_export(char **str, char ***env)
{
	int	ret;

	ret = 0;
	str++;
	if (*str == NULL)
	{
		print_ordered(*env);
		return (ret);
	}
	while (*str)
	{
		if (is_valid_env(*str))
			add_env(*str, env);
		else
			ret = 1;
		str++;
	}
	return (ret);
}
