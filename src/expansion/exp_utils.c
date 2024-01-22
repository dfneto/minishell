/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 12:32:31 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_token	*create_token_split(char *str, t_token *next_token)
{
	t_token	*tok;

	tok = (t_token *)safe_malloc(sizeof(t_token));
	tok->str = str;
	tok->type = STRING;
	tok->next = next_token;
	return (tok);
}

int	is_alpha_or_slash(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

/*
 * Return the dolar position or the last
 * dolar position in case of $$$, for example,
 * or \0 position, starting by i position
 * Returns -1 in case that the str hasn't $
 * and should not be expanded so.
 */
int	get_dolar_position(char *str, int i)
{
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}

/*
 * Check if the str (token->str) is expansible. So you can avoid
 * execute expansion methods in tokens that doesn't even has $
 * (for example: echo, hola etc)
 * and others tokens that doesn't start by an alphacharacter or slash
 * (for example: $1, $/, $' etc)
 */
int	is_expansible(char *str)
{
	int	i;

	i = get_dolar_position(str, 0);
	if (i == -1)
		return (0);
	else if (is_alpha_or_slash(str[i + 1]) || str[i + 1] == '?')
		return (1);
	return (0);
}

/* 
* If it has at least one expansible word returns 1
* Otherwise returns 0.
* It is not implemented, but should deal with cases
* where the first $word is not expansible, like echo "$1 $USER"
*/
int	has_word_expansible(char *str)
{
	return (is_expansible(str));
}

/* TO DO
A função funciona só nos casos que a str começa com $?
echo $? funciona e retorn 0 (ou o exit value atual)
echo abc$? nao funciona e retorna abc$?
// TODO: ao inves de usar 0 e 1 usar dolar position
*/
int	is_dollarquestion_mark(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (0);
}

/*
 * returns: the text before the dolar sign.
 * Ex: for "123$USER" return 123
 */
char	*g_pre_dol(char *str, int *dolar_position, int i) // 0 5
{
	*dolar_position = get_dolar_position(str, i);
	if (*dolar_position == -1)
		return (safe_strdup(""));
	return (safe_substr(str, i, *dolar_position - i));
}
