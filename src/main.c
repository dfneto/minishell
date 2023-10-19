/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:15:09 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/19 16:28:07 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)), char **envp)
{
	return (init_minishell(envp));
}
