/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:27:51 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:28:06 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <stdio.h>

static int	is_n_flag(char const *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **argv, t_env *env, int multi)
{
	int	i;
	int	new_line;

	(void)(env);
	(void)multi;
	i = 0;
	new_line = 1;
	while (is_n_flag(argv[++i]))
		new_line = 0;
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (0);
}
