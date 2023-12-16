/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation_utills.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:02:48 by davifern          #+#    #+#             */
/*   Updated: 2023/11/30 22:03:41 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*create_redirect(char *name, t_type type)
{
	t_redirect *redirect;

	redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (redirect == NULL)
	{
		perror("malloc redirect");
		exit(EXIT_FAILURE);
	}
	redirect->name = name;
	redirect->type = type;
	redirect->next = NULL;
	return (redirect);
}