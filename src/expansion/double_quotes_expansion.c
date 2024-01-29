/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:32 by davifern          #+#    #+#             */
/*   Updated: 2024/01/29 20:39:25 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_text_post_extension(t_token *token, char *exp, int i)
{
	char	*post_expansion;
	char	*tmp1;
	char	*tmp2;

	post_expansion = NULL;
	tmp2 = NULL;
	tmp1 = exp;
	tmp2 = safe_substr(token->str, i, ft_strlen(token->str) - i);
	post_expansion = safe_strjoin(exp, tmp2);
	ft_free(tmp1);
	ft_free(tmp2);
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
	while (token->str[*i] && is_alnum_or_slash(token->str[*i])) //isso pega numero, como? como pega $/ e $1? testar a diferenca
	// while (token->str[*i] && token->str[*i] != ' ' && token->str[*i] != '$')
		(*i)++;
	word_to_expand = safe_substr(token->str, dolar_position, *i
			- dolar_position);
	if (word_to_expand == NULL)
		return (safe_strdup(""));
	if (is_alpha_or_slash(word_to_expand[1])) //$USER
	{     
		word_to_expand = ft_free(word_to_expand);
		word_to_expand = safe_substr(token->str, dolar_position + 1, *i
			- dolar_position - 1); //USER
		word_expanded = safe_strdup(ft_getenv(word_to_expand, env));
	}
	else if (token->next && (token->next->type == DOUBLE_QUOTE || token->next->type == SINGLE_QUOTE)) //$"hola" -> removo o $ e imprimo hola
		word_expanded = safe_strdup("");
	else
		word_expanded = safe_strdup(word_to_expand);
	ft_free(word_to_expand);
	return (word_expanded);
}

char	*join_with_word_expanded(t_token *token, int *i, char *exp, t_env env)
{
	int		dol_pos;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	dol_pos = get_dolar_position(token->str, *i);
	*i = dol_pos + 1;
	tmp = exp;
	tmp2 = g_w_expd(token, i, dol_pos, env);
	exp = safe_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (exp);
}

char	*expand_token_with_pre_dolar(t_token *tok, int *i, t_env env)
{
	int		dol_pos;
	char	*exp;
	char	*tmp;
	char	*tmp2;

	dol_pos = 0;
	exp = NULL;
	tmp = NULL;
	tmp2 = NULL;
	while (tok->str[*i] && dol_pos >= 0)
	{
		tmp = g_pre_dol(tok->str, *i);
		if (exp)
			tmp2 = exp;
		exp = safe_strjoin(tmp2, tmp);
		tmp = ft_free(tmp);
		tmp2 = ft_free(tmp2);
		dol_pos = get_dolar_position(tok->str, *i);
		if (dol_pos >= 0 && tok->str[dol_pos])
			exp = join_with_word_expanded(tok, i, exp, env);
	}
	return (exp);
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
	char	*exp;
	t_token	*head;

	i = 0;
	exp = NULL;
	exp = expand_token_with_pre_dolar(tok, &i, env);
	if (tok->str[i] && tok->str[i] != '$')
	{
		// printf("AQUI\n");
		exp = get_text_post_extension(tok, exp, i);
		// printf("exp depois da expansao: %s\n", exp);
	}
	tok->str = ft_free(tok->str);
	if (tok->type == STRING && !ft_strcmp(exp, ""))
	{
		// tok->str = ft_free(tok->str);
		tok->type = SPC;
	}
	else
		tok->str = exp;
	
	// printf("WAKA\n");
	// exp = ft_free(exp);

	// printf("PATATA\n");
	

	//FAZER ISSO SOMENTE PARA QUANDO O TOK EH STRING:
	if (tok->type == STRING)
	{
		head = remove_spaces_in(&tok);
		tok->str = ft_free(tok->str); //para fazer o abaixo tenho que limpar token->str
		*tok = *head; //isso eh interessante! entender melhor
		head = ft_free(head);
	}


	// printf("ponteiro exp: %p, valor: %s\n", exp, exp);
	// printf("ponteiro tok: %p, valor: %s\n", tok, exp);
	// printf("ponteiro tok->str: %p, valor: %s\n", tok->str, exp);
	// 	str = ft_free(str);
	// 	tok->str = ft_free(tok->str);
	// 	*tok = *head;

	// {
	// 	int	j = 0;
	// 	i = 0;
	// 	char *str = safe_strdup(tok->str);
	// 	t_token *next = tok->next;
	// 	t_token *head = NULL;
	// 	t_token *tmp = NULL;
		
	// 	int max = (int) ft_strlen(str);

	// 	while (i < max)
	// 	{
	// 		while(tok->str[i] && tok->str[i] != ' ')
	// 			i++;
	// 		if (i > j)
	// 		{
	// 			tmp = NULL;
	// 			tmp = create_token(tok->str, j, i - 1, STRING);
	// 			add_token(&head, tmp);
	// 			j = i;
	// 		}
	// 		while (tok->str[i] && tok->str[i] == ' ')
	// 			i++;
	// 		if (i > j)
	// 		{
	// 			tmp = NULL;
	// 			tmp = create_token(tok->str, 0, 0, SPC);
	// 			add_token(&head, tmp);
	// 			j = i;
	// 		}
	// 		if (tok->str[i] == '\0')
	// 			tmp->next = next;
	// 	}
	// 	str = ft_free(str);
	// 	tok->str = ft_free(tok->str);
	// 	*tok = *head;
	// 	head = ft_free(head);
	// }
	return (tok);
}
