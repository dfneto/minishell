/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:07 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 18:08:44 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

static void	case_plus_env(t_env *env, char *name, char *value, int i)
{
	name[i] = '\0';
	ft_setenv(env, name, safe_strdup(value), 0);
}

static int	is_valid_env(char *str, t_env *env)
{
	char	*name;
	char	*value;
	int		i;

	name = ft_strtok(str, "=");
	if (!name || !(ft_isalpha(*name) || *name == '_'))
		return (0);
	i = 1;
	while (name[i] && name[i] != '+')
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	value = ft_strtok(NULL, "\0");
	if (name[i] == '+' && !value)
		return (0);
	else if (name[i] == '+')
		case_plus_env(env, name, value, i);
	else if (!value)
		ft_setenv(env, name, NULL, 0);
	else
		ft_setenv(env, name, safe_strdup(value), 1);
	return (1);
}

/*

 */
int	ft_export(char **argv, t_env *env)
{
	int		ret;
	char	*cpy;

	ret = 0;
	argv++;
	if (*argv == NULL)
		return (print_ordered(*env));
	while (*argv)
	{
		cpy = safe_strdup(*argv);
		if (!is_valid_env(*argv, env))
		{
			ret = 1;
			print_error("br.sh: export: `");
			print_error(cpy);
			print_error("\': not a valid identifier\n");
		}
		if (!ret && (!ft_strcmp(cpy, "PWD") || !ft_strcmp(cpy, "OLDPWD")))
		{
			if (!ft_strcmp(cpy, "PWD"))
			{
				ft_free(env->pwd);
				env->pwd = safe_strdup(cpy);
			}
			else
			{
				ft_free(env->oldpwd);
				env->oldpwd = safe_strdup(cpy);
			}
		}
		free(cpy);
		argv++;
	}
	return (ret);
}
