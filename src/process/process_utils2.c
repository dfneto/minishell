/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:19:14 by davifern          #+#    #+#             */
/*   Updated: 2024/01/23 18:20:35 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*create_default_process(int num_token_str)
{
	t_process	*process;

	process = (t_process *)safe_calloc(1, sizeof(t_process));
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	if (num_token_str > 0)
		process->cmd = (char **)safe_calloc((num_token_str + 1),
				sizeof(char *));
	return (process);
}

/*
 * If the token has str, it means that it is a word (type STR, DOUB ou SING)
 * and so we are going to add this word to the command
 */
void	add_word_to_command(t_process **process, t_token **token, int i)
{
	char	*tmp;

	tmp = safe_strjoin((*process)->cmd[i], (*token)->str);
	if ((*process)->cmd[i])
		free((*process)->cmd[i]);
	(*process)->cmd[i] = tmp;
	(*token) = (*token)->next;
}

/*
 * Vamos para o próximo token, mas dentro do mesmo process->cmd.
 * Quando encontramos um espaço vamos para o próximo token, e
 * se há tokens com strings (num_token_str > 0) significa que
 * devemos adicionar a próxima palavra ao próximo comando
 * e se já temos alguma palavra no comando[i] (process->cmd[i]) e
 * incrementamos i para que a próxima palavra vá em outro comando
 */
int	go_to_next_token(t_token **token, t_process *process, int num_token_str,
		int i)
{
	(*token) = (*token)->next;
	if (num_token_str > 0)
		if (process->cmd[i])
			i++;
	return (i);
}
