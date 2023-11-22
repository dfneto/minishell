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
        if (!ft_strncmp(name, *env, ft_strlen(name))
            && (*env)[ft_strlen(name)] == '=')
            return (ft_substr(*env, ft_strchr(*env, '=') + 1 - *env,
                ft_strchr(*env, '\0') - ft_strchr(*env, '=')));
        env++;
    }
    return (NULL);
}