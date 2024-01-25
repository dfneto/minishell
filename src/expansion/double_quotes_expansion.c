/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2024/01/25 17:46:36 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_text_post_extension(t_token *token, char *exp, int i)
{
	char	*post_expansion;
	char	*tmp;

	post_expansion = NULL;
	tmp = NULL;
	tmp = safe_substr(token->str, i, ft_strlen(token->str) - i);
	post_expansion = safe_strjoin(exp, tmp);
	ft_free(tmp);
	return (post_expansion);
	}

/*
* Get the word expanded
* Returns the word expanded
*/
char	*g_w_expd(t_token *token, int *i, int dolar_position,
		t_env env)
{
	char	*word_to_expand;
	char	*word_expanded;

	word_to_expand = NULL;
	word_expanded = NULL;
	if (token->str[*i] == '?')
	{
		(*i)++;
		return (get_exit_status(env.last_exit));
	}
	while (token->str[*i] && is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = safe_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1);
	if (word_to_expand == NULL)
		return (safe_strdup(""));
	word_expanded = safe_strdup(ft_getenv(word_to_expand, env));
	ft_free(word_to_expand);
	return (word_expanded);
}

/*
* cases: "$USER"
* 			"123$USER" - with pre dolar
*			"123$USER $USER"
*			"123$USER $USER waka"
Let's take the case: "123$USER vaca $USER waka"
	- pre_dolar_text: 123
	- expand_post_dollar will analyse $USER $USER waka
	- pos_last_word_expanded: waka
Another example: "|$USER|"
	- pre_dolar_text: |
	- expand_post_dollar will analyse $USER
	- pos_last_word_expanded: |
* If dolar_position < 0 so it isn't expansible. It is necessary
* because we are going to check and expand every word inside
* the quotes. So waka won't be expanded and so for waka
* in "123$USER $USER waka" the dolar position is -1.
*/
t_token	*expand_double_quote_token(t_token *tok, t_env env)
{
	int		i;
	int		dol_pos;
	char	*exp;
	char	*tmp;
	char *t2;

	i = 0;
	dol_pos = 0;
	exp = NULL;
	while (tok->str[i] && dol_pos >= 0)
	{
		tmp = g_pre_dol(tok->str, i);
		exp = safe_strjoin(exp, tmp);
		tmp = ft_free(tmp);
		dol_pos = get_dolar_position(tok->str, i);
		if (dol_pos >= 0 && tok->str[dol_pos + 1])
		{
			i = dol_pos + 1;
			// exp = safe_strjoin(exp, g_w_expd(tok, &i, dol_pos, env));
			tmp = exp;
			t2 = g_w_expd(tok, &i, dol_pos, env);
			exp = safe_strjoin(tmp, t2);
			free(tmp);
			free(t2);
		}
	}
	if (tok->str[i] && tok->str[i] != '$')
	{
		// char *tmp3;
		// tmp3 = get_text_post_extension(tok, exp, i);
		// free(exp);
		// exp = tmp3;
		tmp = exp;
		exp = get_text_post_extension(tok, exp, i);
		tmp = ft_free(tmp);
		// free(exp);
		// exp = tmp;
	}
	tok->str = ft_free(tok->str);
	tok->str = exp;
	return (tok);
}
