/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:53:01 by davifern          #+#    #+#             */
/*   Updated: 2024/01/23 15:56:57 by davifern         ###   ########.fr       */
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
	t_token *new_token = create_token(NULL, 0, 0, SPC);
	new_token->next = next_tok_after_expand;
	add_token_after(token, new_token);
}

/*
* When you have your expanded_str for something that starts with space, 
* like "    ls   -l  ", you transform the current token in a token space, than
* create a token str (ls), than a token space and finish with a token str (-l)
*/
t_token	*starts_with_space(char *expanded_str, t_token *next_tok_after_expand, t_token *token)
{
	size_t		i;
	int			start;

	i = 1; //TROCAR POR ZERO!?
	start = 0;
	token->type = SPC; //alter o tipo do token para espaco
	token->str = NULL;
	while (expanded_str[i] && i < ft_strlen(expanded_str))
	{
		while (expanded_str[i] && expanded_str[i] == ' ') // avança os espaços
			i++;
		if (start > 0 && expanded_str[i + 1] != '\0')
			add_token_space(&token, next_tok_after_expand);
		start = i;
		while (expanded_str[i] && (expanded_str[i] != ' ' || expanded_str[i + 1] == '\0')) //avanca os char
			i++;
		t_token *new_token = create_token(expanded_str, start, i - 1, STRING);//crio o token com char
		new_token->next = next_tok_after_expand;
		add_token_after(&token, new_token);
	}
	return (token);
}

		/*
		while (expanded_str[i] && expanded_str[i] != ' ') // avança os char	
		{                                                                
			if (expanded_str[i + 1] == ' ') //para quando a palavra expandida começa SEM espaço
			{
				// printf("3\n");
				token->str = safe_substr(expanded_str, start, i - start + 1);  // e altero o primeiro token str
				first_token_alterated = 1;
			}
		}
		*/
/*
* 
* 
*/
t_token	*no_starts_with_space(char *expanded_str, t_token *next_tok_after_expand, t_token *token)
{
	size_t		i;
	int			start;

	i = 0;
	start = 0;
	while (expanded_str[i] && i < ft_strlen(expanded_str))
	{
		while (expanded_str[i] && (expanded_str[i] != ' ' || expanded_str[i + 1] == '\0')) //avanca os char
			i++;
		if (start == 0)
			token->str = safe_substr(expanded_str, start, i - start); //altero a str do primeiro token
		else
		{
			t_token *new_token = create_token(expanded_str, start, i - 1, STRING);//crio o token com char
			new_token->next = next_tok_after_expand;
			add_token_after(&token, new_token);
		}
		start = i;
		while (expanded_str[i] && expanded_str[i] == ' ') // avança os espaços
			i++;
		if (start > 0)
			add_token_space(&token, next_tok_after_expand);
		
	}
	return (token);
}

/*
* It creates a token per each word in expanded_str (it's the str expansion 
* of the token)
//Se depois da expansão eu tenho uma palavra somente vai cair no if e sair
//se depois da expansao eu tenho várias palavras,
	vai cair uma vez no if e outras no else
* Return: the last part of the token expanded or the token in the
* case that the expansion is null
* ex: a="ls   -l    -a  -F   "
* $a patata: returns the token spc with token->next = patata e 
* o token anterior ao spc sendo	-F
*/
t_token	*create_tok_per_word_in(char *expanded_str, t_token *next_tok_after_expand, t_token *token)
{
	size_t		i;
	int			start;

	i = 0;
	start = 0;
	// printf("expanded_str: <%s>\n", expanded_str);
	if (expanded_str[i] && expanded_str[i] == ' ')
		return (starts_with_space(expanded_str, next_tok_after_expand, token));
	// else //if (expanded_str[i] && expanded_str[i] != ' ')
	// 	return (no_starts_with_space(expanded_str, next_tok_after_expand, token));
	//TODO: ISSO DEVE SUBSTITUR TODO O WHILE ABAIXO
	
	while (i < ft_strlen(expanded_str))
	{
		while (expanded_str[i] && expanded_str[i] != ' ') // avança os char
		{                                                                
			if (expanded_str[i + 1] == ' ' && start == 0) //para quando a palavra expandida começa SEM espaço
				token->str = safe_substr(expanded_str, start, i - start + 1);  // e altero o primeiro token str
			else if (expanded_str[i + 1] == ' ' || expanded_str[i + 1] == '\0') // e cria um token str 
			{ 
				t_token *new_token = create_token(expanded_str, start, i, STRING);
				new_token->next = next_tok_after_expand;
				add_token_after(&token, new_token);
			}
			i++;
		}
		while (expanded_str[i] && expanded_str[i] == ' ') // avança os espaços
			i++;
		if (expanded_str[i - 1] == ' ' && expanded_str[i] != ' ')
			add_token_space(&token, next_tok_after_expand);
		start = i;
	}
	return (token);
}