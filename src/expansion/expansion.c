/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/11/18 16:28:26 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = ft_substr(token->str,
			dolar_position + 1, *i - dolar_position - 1);
	return (getenv(word_to_expand));
}

char	*get_pre_dolar_text(char *str, int *dolar_position, int i)
{
	*dolar_position = get_dolar_position(str, i);
	return (ft_substr(str, i, *dolar_position - i));
}

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
//retorna o token expandido e no caso em que a expansão gere vários tokens, retorna o último token da expansão
t_token	*expand(t_token *token)
{
	if (token->type == DOUBLE_QUOTE)
		return (expand_double_quote_token(token));
	else
		return (expand_token_int_n_tokens(token)); 
}

//TODO: implementar
char	*get_exit_status()
{
	return ("0");
}

/*
* If the token to be expand is $? get the exit status.
* Otherwise check if it's expansible and expand it.
*/
int	check_and_expand(t_token *token)
{
	if (is_dollarquestion_mark(token->str))
		token->str = get_exit_status();
	else if (is_expansible(token->str))
		token = expand(token);
	return (1);
}

/*
* Expand al the tokens of type DOUBLE_QUOTE or STRING
*/
int	expansion(t_token *first_token)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE
			|| first_token->type == STRING)
			check_and_expand(first_token);
		first_token = first_token->next;
	}
	return (0);
}
