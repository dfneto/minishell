/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2024/01/28 20:45:27 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Returns: the token expanded and in case that the expansion
 * generate multiple tokens, returns the last token from the 
 * expansion.
 * Details:
 * If the token type is DOUBLE_QUOTE it must be expanded equally
 * as it is in the env. Ex:
 * In case that we have in env $a="ls  -l  -a  -F"
 * "$a" should produce one token with token->str = "ls  -l  -a  -F"
 * If the token type is STRING it must be expanded
 * without the spaces. Ex:
 * In case that we have in env $a="ls  -l  -a  -F"
 * $a should produce four tokens, each token->str would have
 * ls, -l, -a, -F, respectively, and return the next token, in this
 * case null. But, if: $a waka, the token to be returned is <spc>
 */
t_token	*expand_according_to_type(t_token *token, t_env env)
{
	// return expand_double_quote_token(token, env);
	if (token->type == DOUBLE_QUOTE)
		return (expand_double_quote_token(token, env));
	return (expand_string_token(token, env));
}

/* TO DO
Função só funciona com o caso $? sozinho
Refazer junto com a is_dolarquestion_mark
-->> proteger malloc (ft_itoa)
 */
char	*get_exit_status(int last_exit)
{
	return (safe_itoa(last_exit));
}

// int	is_quotes(char *str)
// {
// 	printf("verificnado o token %s\n", str);
// 	int	dolar_position;

// 	dolar_position = get_dolar_position(str, 0);
// 	if (dolar_position == -1)
// 		return (0);
// 	if (str[dolar_position + 1] == 34 || str[dolar_position + 1] == 39)
// 		return (1);
// 	return (0);
// }

/*
 * token: it is one word of the first_token.
 * The "else if" deals with cases like: $"   t  hi   t    " 
 * or $'   t  hi   t    ' (tests 198-200) and them remove the token $
 * TODO: idealmente nesses casos (198-200) seria remover o token $ ao
 * invés de apagá-lo e seria bom ter um ponteiro previous
 */
int	check_and_expand(t_token *token, t_env env)
{
	if (has_word_expansible(token->str))
	// if (ft_strchr(token->str, '$'))
		token = expand_according_to_type(token, env);
	else if (token->str[0] == '$' && token->next
		&& (token->next->type == DOUBLE_QUOTE
			|| token->next->type == SINGLE_QUOTE))
	{
		token->str = ft_free(token->str);
		token->str = safe_strdup("");
	}
	return (1);
}

/*
 * For each token of the first_token it will:
 * If the token type is DOUBLE_QUOTE or STRING, 
 * check if it is expansible and expand it, 
 * otherwise does nothing.
 * first_token: is all the input text typed by the user
 */
int	expansion(t_token *first_token, t_env env)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE || first_token->type == STRING)
			check_and_expand(first_token, env);
		first_token = first_token->next;
	}
	return (0);
}
