/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:50 by davifern          #+#    #+#             */
/*   Updated: 2024/01/29 22:10:42 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_add_token_space(t_token **head, int i)
{
	t_token	*tmp;

	tmp = NULL;
	tmp = create_token(0, 0, 0, SPC);
	add_token(head, tmp);
	return (i);
}

int	create_add_token_string(t_token **head, char *str, int j, int i)
{
	t_token	*tmp;

	tmp = NULL;
	tmp = create_token(str, j, i - 1, STRING);
	add_token(head, tmp);
	return (i);
}

t_token	*remove_spaces_in(t_token **token)
{
	int		i;
	int		j;
	char	*str;
	t_token	*head;

	i = 0;
	j = 0;
	head = NULL;
	str = safe_strdup((*token)->str);
	while (i < (int) ft_strlen(str))
	{
		while (str[i] && str[i] != ' ')
			i++;
		if (i > j)
			j = create_add_token_string(&head, str, j, i);
		while (str[i] && str[i] == ' ')
			i++;
		if (i > j)
			j = create_add_token_space(&head, i);
		if (str[i] == '\0')
			get_last_token(head)->next = (*token)->next;
	}
	ft_free(str);
	return (head);
}

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
 * returns: the text before the dolar sign.
 * Ex: for "123$USER" return 123
 */
char	*g_pre_dol(char *str, int start)
{
	int	dolar_position;

	dolar_position = get_dolar_position(str, start);
	if (dolar_position == -1)
		return (safe_strdup(""));
	return (safe_substr(str, start, dolar_position - start));
}
