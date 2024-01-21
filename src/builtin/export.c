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

/* static int	is_valid_env(char *str)
{
	// printf("%s", str);
	if (!(ft_isalpha(*str) || *str == '_'))
		return (-1);
	str++;
	while (*str && *str != '=' && *str != '+')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (-1);
		str++;
	}
	if (*str == '+')
	{
		str++;
		if (*str == '=')
			return (0);
		return (-1);
	}
	if (*str)
		return (1);
	return (2);
} */

static void	case_plus_env(t_env *env, char *name, char *value, int i)
{
	name[i] = '\0';
	ft_setenv(env, safe_strdup(name), safe_strdup(value), 0);
}

static int	is_valid_env2(char *str, t_env *env)
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
		ft_setenv(env, safe_strdup(name), value, 0);
	else
		ft_setenv(env, safe_strdup(name), safe_strdup(value), 1);
	return (1);
}

/*

 */
int	ft_export(char **argv, t_env *env)
{
	int		ret;
	char	*cpy;

	(void)last_exit;
	ret = 0;
	argv++;
	if (*argv == NULL)
		return (print_ordered(*env));
	while (*argv)
	{
		cpy = safe_strdup(*argv);
		if (!is_valid_env2(*argv, env))
		{
			ret = 1;
			print_error("Brazilian Shell: export: `");
			print_error(cpy);
			print_error("\': not a valid identifier\n");
		}
		free(cpy);
		argv++;
	}
	return (ret);
}
