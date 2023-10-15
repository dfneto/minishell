/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation_utills.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:02:48 by davifern          #+#    #+#             */
/*   Updated: 2023/10/15 17:09:53 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"


t_process	*create_process(t_token *token)
{
	t_process	*process;

	process = NULL;
	
	process->next = NULL;
	process->prev = NULL;
	return (process);	
}
