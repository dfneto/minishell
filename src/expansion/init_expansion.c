/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/11/22 15:28:54 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *lukita_get_expansion(char *str, int *i, t_env env, int last_exit)
{
	int j;
	char *tmp;
	char *ret;

	j = 0;
	if (!str[j])
	{
		(*i)++;
		return ("$");
	}
	if (str[j] == '?')
	{
		(*i) += 2;
		return (ft_itoa(last_exit));
	}
	if (!ft_isalpha(str[j]) && str[j] != '_')
	{
		(*i)++;
		return ("$");
	}
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	tmp = ft_substr(str, 0, j);
	ret = ft_getenv(tmp, env);
	free(tmp);
	(*i) += j + 1;
	return (ret);
}

char	*lukita_str_expand(char *str, t_env env, int last_exit)
{
	char *expanded_str;
	char *tmp;
	int	i;
	int start;

	i = 0;
	expanded_str = NULL;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		if (i != start)
		{
			tmp = expanded_str;
			expanded_str = ft_strjoin(tmp, ft_substr(str, start, i - start));
			if (tmp)
				free(tmp);
		}
		if (str[i] && str[i] == '$')
		{
			tmp = expanded_str;
			expanded_str = ft_strjoin(tmp, lukita_get_expansion(str + i + 1, &i, env, last_exit));
			if (tmp)
				free(tmp);
		}
	}
	free(str);
	return (expanded_str);
}

t_token *lukita_split_token(t_token *token)
{
	t_token *tmp;
	t_token *last;
	char *tk;

	tk = ft_strtok(token->str, " \t\n\r\v\f");
	last = token;
	tk = ft_strtok(NULL, " \t\n\r\v\f");
	while (tk)
	{
		tmp = ft_calloc(1, sizeof(t_token));
		tmp->type = SPC;
		last->next = tmp;
		last = last->next;
		tmp = ft_calloc(1, sizeof(t_token));
		tmp->type = STRING;
		tmp->str = ft_strdup(tk);
		last->next = tmp;
		last = last->next;
		tk = ft_strtok(NULL, " \t\n\r\v\f");
	}
	
		

	return (token);
}

int ft_isspace(char ch) {
    return (ch == ' ' || ch == '\t' || 
		ch == '\n' || ch == '\r' || 
		ch == '\v' || ch == '\f');
}


int lukita_str_has_space(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}


t_token	*lukita_expand(t_token *token, t_env env, int last_exit)
{
//	printf("%s\n", token->str);
	token->str = lukita_str_expand(token->str, env, last_exit);
//	printf("%s\n", token->str);
	if (token->type == DOUBLE_QUOTE)
		return (token);
	else if (lukita_str_has_space(token->str))
		return (lukita_split_token(token));
	return (token);
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
// retorna o token expandido e no caso em que a expansão gere vários tokens,
//	retorna o último token da expansão
t_token	*expand(t_token *token, t_env env)
{
	if (token->type == DOUBLE_QUOTE)
		return (expand_double_quote_token(token, env));
	else
		return (expand_token_int_n_tokens(token, env));
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

/*
 * If the token to be expand is $? get the exit status.
 * Otherwise check if it's expansible and expand it.
 */
int	check_and_expand(t_token *token, int last_exit, t_env env)
{
	// TODO: testar 123$? -> se resolver por aqui retiramos o last do ft_getenv
	if (is_dollarquestion_mark(token->str))
		token->str = get_exit_status(last_exit);
	else if (is_expansible(token->str))
		token = expand(token, env);
	return (1);
}

/*
 * Expand al the tokens of type DOUBLE_QUOTE or STRING
 */
int	expansion(t_token *first_token, int last_exit, t_env env)
{
	while (first_token)
	{
		//print_token(first_token);
		if ((first_token->type == DOUBLE_QUOTE || first_token->type == STRING) &&
				strchr(first_token->str, '$'))
				{
					if (ft_strlen(first_token->str) == 1 && (first_token->next && first_token->next->str))
					{
						free(first_token->str);
						first_token->str = ft_strdup("");
					}
					else
						first_token = lukita_expand(first_token, env, last_exit);
				}
		first_token = first_token->next;
	}
	return (0);
}
