/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:53:01 by davifern          #+#    #+#             */
/*   Updated: 2023/11/24 15:06:11 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_after(t_token **token, t_token *new_token)
{
	(*token)->next = new_token;
    (*token) = new_token;
}

/*
* Remove an certain amount of chars (size_to_remove) 
* from a string str starting from start char and
* return: the new string
*/
char	*remove_pre_dolar_text(char *str, int start)
{
	return (ft_substr(str, start, ft_strlen(str) - start));
}

t_token *set_token_str(t_token *token, char *value)
{
	token->str = ft_strdup(value);
	return token;
}

/*
* It creates a token per each word in expanded_str (it's the str expansion of the token)
//Se depois da expansão eu tenho uma palavra somente vai cair no if e sair
//se depois da expansao eu tenho várias palavras, vai cair uma vez no if e outras no else
* Return: the last part of the token expanded or the token in the 
* case that the expansion is null
* ex: a="ls   -l    -a  -F   " 
* $a patata: returns the token spc with token->next = patata e o token anterior ao spc sendo -F
*/
t_token	*create_tok_per_word_in(char *expanded_str, char *pre_dolar, t_token *next_tok_after_expand, t_token *token)
{
	(void)pre_dolar;
	size_t			i;
	int			start;
	int			first_token_alterated;
	
	i = 0;
	first_token_alterated = 0;
	start = 0;
	while(i < ft_strlen(expanded_str)) 
	{ 
		while (expanded_str[i] && expanded_str[i] == ' ')//avança os espaços
		{ 
			if (expanded_str[i + 1] != ' ' && first_token_alterated == 0) //e cria um token espaço
			{
				token->type = SPC;
				first_token_alterated = 1;
			}
			else if (expanded_str[i + 1] != ' ' && first_token_alterated == 1)
			{
				t_token *new_token = create_token_with_next(expanded_str, start, i - 1, SPC, next_tok_after_expand);
				add_token_after(&token, new_token);
			}
			i++;
		}
		start = i;
		while (expanded_str[i] && expanded_str[i] != ' ')
		{	//avança os char 
			if (expanded_str[i + 1] == ' ' && first_token_alterated == 0) //e altero o primeiro token str
			{
				token->str = ft_substr(expanded_str, start, i - start + 1);
				first_token_alterated = 1;
			}
			else if ((expanded_str[i + 1] == ' ' || expanded_str[i + 1] == '\0') && first_token_alterated == 1) //e cria um token str
			{
				t_token *new_token = create_token_with_next(expanded_str, start, i, STRING, next_tok_after_expand);
				add_token_after(&token, new_token);
			}		
			i++;
		}
	}
	return (token);
}