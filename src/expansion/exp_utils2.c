/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:53:01 by davifern          #+#    #+#             */
/*   Updated: 2024/01/25 19:45:47 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_after(t_token **token, t_token *new_token)
{
	(*token)->next = new_token;
	(*token) = new_token;
}

void	add_token_space(t_token **token, t_token *next_tok_after_expand)
{
	t_token	*new_token;

	new_token = create_token(NULL, 0, 0, SPC);
	new_token->next = next_tok_after_expand;
	add_token_after(token, new_token);
}

/*
 * When you have your expanded_str for something that starts with space,
 * like "    ls   -l  ", you transform the current token in a token space, than
 * create a token str (ls), than a token space and finish with a token str (-l)
 * expanded_str can also be: "   ls" or "    ls   ", for example.
 */
t_token	*starts_with_space(char *expanded_str, t_token *next_tok_after_expand,
		t_token *token)
{
	size_t	i;
	int		start;
	t_token	*new_token;

	i = 0;
	start = 0;
	token->type = SPC;
	token->str = NULL;
	while (expanded_str[i] && i < ft_strlen(expanded_str))
	{
		while (expanded_str[i] && expanded_str[i] == ' ')
			i++;
		if (start > 0 && expanded_str[i + 1] != '\0')
			add_token_space(&token, next_tok_after_expand);
		start = i;
		while (expanded_str[i] && (expanded_str[i] != ' '
				|| expanded_str[i + 1] == '\0'))
			i++;
		new_token = create_token(expanded_str, start, i - 1, STRING);
		new_token->next = next_tok_after_expand;
		add_token_after(&token, new_token);
	}
	return (token);
}

/*
 * When you have your expanded_str for something that DOESN'T starts with space,
 * like "ls   -l  ", you transform the current token in a token space, than
 * create a token str (ls), than a token space and finish with a token str (-l)
 * expanded_str can also be: "    ls   ", for example.
 */
t_token	*no_starts_with_space(char *expanded_str,
		t_token *next_tok_after_expand, t_token *token)
{
	size_t	i;
	int		start;
	t_token	*new_token;

	i = 0;
	start = 0;
	while (i < ft_strlen(expanded_str))
	{
		while (expanded_str[i] && expanded_str[i] != ' ')
			i++;
		if (expanded_str[i] == ' ' && start == 0)
			token->str = safe_substr(expanded_str, start, i - start);
		else if (expanded_str[i] == ' ' || expanded_str[i] == '\0')
		{
			new_token = create_token(expanded_str, start, i - 1, STRING);
			new_token->next = next_tok_after_expand;
			add_token_after(&token, new_token);
		}
		while (expanded_str[i] && expanded_str[i] == ' ')
			i++;
		if (expanded_str[i - 1] == ' ' && expanded_str[i] != ' ')
			add_token_space(&token, next_tok_after_expand);
		start = i;
	}
	return (token);
}

/*
 * It creates a token per each word in expanded_str (it's the str expansion
 * of the token)
 * Return: the last part of the token expanded or the token in the
 * case that the expansion is null
 * ex: a="ls   -l    -a  -F   "
 * $a patata: returns the token spc with token->next = patata e
 * o token anterior ao spc sendo	-F
 */
t_token	*create_tok_per_word_in(char *expanded_str,
		t_token *next_tok_after_expand, t_token *token)
{
	size_t	i;
	t_token	*token_expanded;

	i = 0;
	token_expanded = NULL;
	if (expanded_str[i] && expanded_str[i] == ' ')
		token_expanded = starts_with_space(expanded_str,
				next_tok_after_expand, token);
	else
		token_expanded = no_starts_with_space(expanded_str,
				next_tok_after_expand, token);
	expanded_str = ft_free(expanded_str);
	return (token_expanded);
}
