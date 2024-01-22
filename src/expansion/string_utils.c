/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:00:06 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 17:05:49 by davifern         ###   ########.fr       */
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

/*
* Receive a token starting by $. Ex: $a
* Return: the last part of the token expanded or the token in the 
* case that the expansion is null
* ex: a="ls   -l    -a  -F   " 
* $a patata: returns the token -F with token->next = patata
*/
t_token	*expand_token_dolar(t_token *token, t_env env)
{
	char		*expanded_str;
	t_token		*next_tok_after_expand;

	next_tok_after_expand = token->next;

	//ADICIONEI ESSE TESTE PARA EVITAR DE CRIAR O TOKEN QUANDO A VARIAVEL NAO EXISTE NO ENV
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
	//if (expanded_str == NULL)     -> RETIREI ESSA PARTE PORQUE O SAFE STRDUP NUNCA VAI RETORNAR NULL!
	//	return (set_token_str(token, ""));
	token->str = NULL;
	if (has_space(expanded_str))
		return (create_tok_per_word_in(expanded_str, next_tok_after_expand, token));
	else //TODO: talvez deva alterar o compartamento de quando a string expandida (ex: $USER -> david) não tenha espaço para se 
	{	//assemelhar ao caso em que tem espaço, ou não tbm. Porque se eu tenhoo que token->str tem um valor diferente de nulo tbm da erro de segfault
		token->str = expanded_str;
		return (token);
	}
}

/*
* Expand every token dolar created in the split
*/
t_token	*expand_tokens_created(t_token *token, int num, t_env env)
{
	int			i;
	t_token 	*aux;

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
