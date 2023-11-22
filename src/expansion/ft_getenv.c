/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:31:08 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/22 13:31:10 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// while is alnum _
char    *ft_getenv(char *name, char **env, int last_exit)
{
    if (name[0] == '?')
        return (ft_itoa(last_exit));
    while (*env)
    {

    }
}