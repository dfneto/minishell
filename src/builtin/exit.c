/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:28:19 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/14 12:29:26 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

static int	is_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **argv, t_env *env, int last_exit)
{
	(void)env;
	//printf("exit\n");
	argv++;
	if (argv[0] == NULL)
		exit(last_exit);
	if (is_num(argv[0]) && argv[1] == NULL)
		exit(ft_atoi(argv[0]));
	else if (!is_num(argv[0]))
	{
		print_error("Brazilian Shell: exit: ");
		print_error(argv[0]);
		print_error(": numeric argument required\n");
		exit(255);
	}
	print_error("Brazilian Shell: exit: too many arguments\n");
	return (1);
}
