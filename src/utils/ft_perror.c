/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:31:31 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/14 11:31:33 by lsulzbac         ###   ########.fr       */
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
	print_error("Brazilian Shell: ");
	if (func_name)
		print_error(func_name);
	perror(msg);
	return (exit_status);
}
