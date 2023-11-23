/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:27:37 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/14 14:27:39 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	execute_builtins(char **argv, t_env *env, int last_exit,
		t_builtin functions[])
{
	int	i;

	i = 0;
	while (i < BUILTINS_NUM)
	{
		if (!ft_strcmp(functions[i].name, argv[0]))
			return (functions[i].function(argv, env, last_exit));
		i++;
	}
	return (-1);
}
