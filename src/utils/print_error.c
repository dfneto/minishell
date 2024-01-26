/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:06:00 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 18:08:44 by davifern         ###   ########.fr       */
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
	print_error("br.sh: ");
	print_error(cmd);
	print_error(": command not found\n");
	return (127);
}
