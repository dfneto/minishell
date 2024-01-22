/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:00:06 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 19:50:30 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * TODO: In the str, if it occurs an $? in str it gets the value
 * Ex: echo hola$?tudobem$? -> hola0tudobem0
 * But it is not implemented.
 */
char	*expand_dollar_question(char *str, t_env env)
{
	(void)str;
	return (safe_strdup(get_exit_status(env.last_exit)));
}

/*
 * Receive a token starting by $. Ex: $a
 * Return: the last part of the token expanded or the token in the
 * case that the expansion is null
 * ex: a="ls   -l    -a  -F   "
 * $a patata: returns the token -F with token->next = patata
 */
t_token	*expand_token_dolar(t_token *token, t_env env)
{
	char	*expanded_str;
	t_token	*next_tok_after_expand;

	next_tok_after_expand = token->next;
	if (!exist_in_env(token->str, env))
	{
		token->str = NULL;
		token->type = SPC;
		return (token);
	}
	if (token->str == NULL)
		expanded_str = safe_strdup("");
	else
		expanded_str = safe_strdup(ft_getenv(token->str, env));
	token->str = NULL;
	if (has_space(expanded_str))
		return (create_tok_per_word_in(expanded_str, next_tok_after_expand,
				token));
	else
	{
		token->str = expanded_str;
		return (token);
	}
}

/*
 * Expand every token dolar created in the split
 */
t_token	*expand_tokens_created(t_token *token, int num, t_env env)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = NULL;
	while (token && i < num)
	{
		aux = expand_token_dolar(token, env);
		token = aux->next;
		i++;
	}
	return (token);
}
