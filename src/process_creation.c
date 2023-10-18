/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2023/10/18 21:51:35 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*process_creation(t_token *first_token)
{
	t_process	*first_process;
	t_process	*process;

	first_process = NULL;
	process = NULL;
	while (first_token)
	{
		//se token for um comando
			//if(!process->cmd)
				//process->cmd = token
			//else:	
				//acredito que devo adicionar o comando como um parâmetro ou dar um erro
		//se token for um argumento
			//adicionar o token aos argumentos do processo
		if (first_token->type == PIPE)
			//criar e adicionar processo a lista de processos
			//add_process(&first_process, process);
		first_token = first_token->next;
	}
	return (first_process);
}
