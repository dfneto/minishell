/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2024/01/21 13:05:08 by davifern         ###   ########.fr       */
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
 */
int	get_dolar_position(char *str, int i)
{
	if (str[i] == '\"')
		i++;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '\0')
		// return i;
		return (-1); //coloquei -1 para ser identificado no is_expansible e nao ser expandido nesse caso de \0
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}

// Modifiquei aqui pq dava um erro quando passava o valgrind.
// Em casos sem expansão o i retornava fora do tamanho da str
// EX: ls retornava um i = 3 e dai quando ia pro if tava fora 
// e podia dar seg fault (nao sei pq nao dava...)
// Retirei tambem o is alnum or slash pq nao acho que deve ser testado aqui

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

/* TO DO
A função funciona só nos casos que a str começa com $?
echo $? funciona e retorn 0 (ou o exit value atual)
echo abc$? nao funciona e retorna abc$?
*/
int	is_dollarquestion_mark(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (0);
}

/*
 * Jump the spaces in a string starting in the i position of the string
 * Return: the indice of the first not space char
 */
// int	ignore_spaces(char *str, int i)
// {
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	return (i);
// }

char	*get_pre_dolar_text(char *str, int *dolar_position, int i) // 0 5
{
	*dolar_position = get_dolar_position(str, i);
	// printf("palavra %s - dolar position: %d\n", str, *dolar_position);
	if (*dolar_position == -1)
		return (safe_strdup(""));
	// printf("i: %d, dolar: %d\n", i, *dolar_position);
	return (safe_substr(str, i, *dolar_position - i));
}
