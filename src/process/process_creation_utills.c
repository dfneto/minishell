/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation_utills.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:02:48 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 17:27:38 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*create_redirect(char *name, t_type type)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)safe_calloc(1, sizeof(t_redirect));
	redirect->name = name;
	redirect->type = type;
	redirect->next = NULL;
	return (redirect);
}

void	clean_redirects(t_redirect *redirect)
{
	t_redirect	*tmp;

	while (redirect)
	{
		tmp = redirect->next;
		if (redirect->name)
			free(redirect->name);
		free(redirect);
		redirect = tmp;
	}
}
