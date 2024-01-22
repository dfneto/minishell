/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:00:06 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 13:15:59 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* In the str, if it occurs and $? it gets the value
* Ex: echo hola$?tudobem$? -> hola0tudobem0
*/
char    *expand_dollar_question(char *str, t_env env)
{
    (void) str;
    return (safe_strdup(get_exit_status(env.last_exit)));
}