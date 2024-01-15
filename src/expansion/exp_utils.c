/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2024/01/15 20:23:51 by davifern         ###   ########.fr       */
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
		return (i);
	while (str[i] && str[i] == '$')
		i++;
	return (i - 1);
}

/*
Modifiquei aqui pq dava um erro quando passava o valgrind.
Em casos sem expansão o i retornava fora do tamanho da str
EX: ls retornava um i = 3 e dai quando ia pro if tava fora e podia dar seg fault (nao sei pq nao dava...)

Retirei tambem o is_alnum_or_slash pq nao acho que deve ser testado aqui
*/
int	is_expansible(char *str)
{
	int	i;

	i = get_dolar_position(str, 0);
	if (str[i]) //TODO: voltar para is_alpha_or_slash? Ou REMOVER TODO ESSE METODO JA QUE EU TRATO AS EXCECOES DENTRO DOS 
	//METODOS SEGUIHNTES expand_double_quote_token E expand_token_int_n_tokens
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
int	ignore_spaces(char *str, int i)
{
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*get_pre_dolar_text(char *str, int *dolar_position, int i)
{
	*dolar_position = get_dolar_position(str, i);
	return (safe_substr(str, i, *dolar_position - i));
}