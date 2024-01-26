/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:31:31 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/26 18:08:44 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Trocar para int e retornar ele em caso de falha,
Receber esse int por variavel? */
int	ft_perror(char *msg, char *func_name, int exit_status)
{
	print_error("br.sh: ");
	if (func_name)
		print_error(func_name);
	perror(msg);
	return (exit_status);
}
