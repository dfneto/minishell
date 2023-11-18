/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:58 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/14 12:52:00 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	init_builtins(t_builtin array[])
{
	array[0].name = "echo";
	array[0].function = ft_echo;
	array[1].name = "cd";
	array[1].function = ft_cd;
	array[2].name = "pwd";
	array[2].function = ft_pwd;
	array[3].name = "export";
	array[3].function = ft_export;
	array[4].name = "unset";
	array[4].function = ft_unset;
	array[5].name = "env";
	array[5].function = ft_env;
	array[6].name = "exit";
	array[6].function = ft_exit;
}
