/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:06:00 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/15 11:06:49 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <minishell.h>

int	print_error(char *str)
{
	return (write(2, str, ft_strlen(str)));
}

int	print_cmd_not_found(char *cmd)
{
	print_error("Brazilian Shell: ");
	print_error(cmd);
	print_error(": command not found\n");
	return (127);
}
