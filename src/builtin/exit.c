/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:28:19 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 18:08:44 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

static int	compare_pos(char *str)
{
	int	my_len;
	int	max_len;

	if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	my_len = ft_strlen(str);
	max_len = ft_strlen(L_MAX);
	if (my_len < max_len)
		return (0);
	if (my_len > max_len)
		return (1);
	if (ft_strcmp(str, L_MAX) > 0)
		return (1);
	return (0);
}

static int	compare_neg(char *str)
{
	int	my_len;
	int	max_len;

	str++;
	while (*str == '0')
		str++;
	my_len = ft_strlen(str);
	max_len = ft_strlen(L_MIN);
	if (my_len < max_len)
		return (0);
	if (my_len > max_len)
		return (1);
	if (ft_strcmp(str, L_MIN) > 0)
		return (1);
	return (0);
}

static int	is_too_big(char *str)
{
	if (*str == '-')
		return (compare_neg(str));
	else
		return (compare_pos(str));
}

static int	is_num(char *str)
{
	char	*cpy;

	str = safe_strtrim(str, " ");
	cpy = str;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (free(cpy), 0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (free(cpy), 0);
		str++;
	}
	if (is_too_big(cpy))
		return (free(cpy), 0);
	free(cpy);
	return (1);
}

int	ft_exit(char **argv, t_env *env, int multi)
{
	argv++;
	if (!multi)
		print_error("exit\n");
	if (*argv && !ft_strcmp(*argv, "--"))
		argv++;
	if (argv[0] == NULL)
		exit(env->last_exit);
	if (argv[1] == NULL && is_num(argv[0]))
		exit(ft_atoi(argv[0]));
	else if (!is_num(argv[0]))
	{
		print_error("br.sh: exit: ");
		print_error(argv[0]);
		print_error(": numeric argument required\n");
		exit(255);
	}
	print_error("br.sh: exit: too many arguments\n");
	return (EXIT_FAILURE);
}
