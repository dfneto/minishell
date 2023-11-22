/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/11/22 12:34:08 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * If the token type is DOUBLE_QUOTE it must be expanded equally
 * as is in the env. Ex:
 * In case that we have in env $a="ls  -l  -a  -F"
 * "$a" should produce one token with token->str = "ls  -l  -a  -F"
 * If the token type is STRING it must be expanded
 * without the spaces. Ex:
 * In case that we have in env $a="ls  -l  -a  -F"
 * $a should produce four tokens, each token->str would have
 * ls, -l, -a, -F, respectively
 */
// retorna o token expandido e no caso em que a expansão gere vários tokens,
//	retorna o último token da expansão
t_token	*expand(t_token *token)
{
	if (token->type == DOUBLE_QUOTE)
		return (expand_double_quote_token(token));
	else
		return (expand_token_int_n_tokens(token));
}

/* TO DO
Função só funciona com o caso $? sozinho
Refazer junto com a is_dolarquestion_mark
-->> proteger malloc (ft_itoa) 
 */
char	*get_exit_status(int last_exit)
{
	return (ft_itoa(last_exit));
}

/*
 * If the token to be expand is $? get the exit status.
 * Otherwise check if it's expansible and expand it.
 */
int	check_and_expand(t_token *token, int last_exit)
{
	if (is_dollarquestion_mark(token->str))
		token->str = get_exit_status(last_exit);
	else if (is_expansible(token->str))
		token = expand(token);
	return (1);
}

/*
 * Expand al the tokens of type DOUBLE_QUOTE or STRING
 */
int	expansion(t_token *first_token, int last_exit)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE || first_token->type == STRING)
			check_and_expand(first_token, last_exit);
		first_token = first_token->next;
	}
	return (0);
}
