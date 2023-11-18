/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:37 by davifern          #+#    #+#             */
/*   Updated: 2023/11/18 15:03:36 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token_split(char *str)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = str;
	tok->type = STRING;
	tok->next = NULL;
	return (tok);
}


//return the last part of the token expanded or the token in case that the expansion is null
//ex: a="ls   -l    -a  -F   " 
//$a patata: retorna o token -F com este apontando ao token patata
t_token	*expand3(t_token *token)
{
	printf("expandindo split_token: %s\n", token->str);
	size_t			i;
	int			start;
	char		*token_str;
	t_token		*aux;
	t_token		*new_token;
	t_token		*last_token;

	new_token = NULL;
	last_token = token->next;
	token_str = getenv(token->str);
	if (token_str == NULL)
	{
		token->str = ft_strdup("");
		return token;
	}
	printf("expansão: %s\n", token_str);
	token->str = NULL;
	aux = token;
	i = 0;
	while(i < ft_strlen(token_str))
	{
		if (token_str[i] != ' ') 
		{
			start = i;
			while (token_str[i] && token_str[i] != ' ') //serve para quitar os espaços
				i++;
			if (!token->str) //so entra a primeira vez para cada split_token
				token->str = ft_substr(token_str, start, i - start);
			else
			{
				new_token = create_token(token_str, start, i - 1, STRING);
				new_token->next = last_token;
				aux->next = new_token;
				aux = new_token;
			}
		}
		i++;
	}
	return aux; 
}

//a $USER$USER a - ok
//a $a$a$a a - ok
t_token	*expand1(t_token *token) //$a$a$a
{
	int			i;
	char		**split = NULL;
	t_token 	*aux;
	t_token 	*last_token; 
	t_token 	*new_token;

	//inicialização
	i = 0;
	new_token = NULL;
	printf("Token a ser expandido: %s\n", token->str);
	split = ft_split(token->str, '$');
	aux = token;
	last_token = token->next;
	token->str = split[0];
	printf("split #%d que deve ser expandido: %s\n", 0, split[0]);
	int j = 1;
	while (split[j]) //$a$b$c => token $a, token $b, token $c
	{
		printf("split #%d que deve ser expandido: %s\n", j, split[j]);
		new_token = create_token_split(split[j]);
		new_token->next = last_token;
		aux->next = new_token;
		aux = new_token;
		j++;
	}
	printf("Lista de tokens recebidos:\n");
	print_list(token);
	while (token && i < j) //agora vou expandir cada split_token
	{
		last_token = expand3(token);
		token = last_token->next; //ou token = next token do ultimo token expandido
		i++;
	}
	return token;
}

//return the last part of the token expanded or the token in case that the expansion is null
//ex: a="ls   -l    -a  -F   " 
//$a patata: => token ls, token -l, token -a, token -F
//e retorna o token -F com este apontando ao token patata
t_token	*expand4(t_token *token, char *pre_dolar)
{
	printf("expandindo split_token: %s\n", token->str);
	size_t			i;
	int			start;
	char		*token_str;
	t_token		*aux;
	t_token		*new_token;
	t_token		*last_token;

	new_token = NULL;
	last_token = token->next;
	token_str = getenv(token->str);
	if (token_str == NULL)
	{
		token->str = ft_strdup("");
		return token;
	}
	token->str = NULL;
	aux = token;
	i = 0;
	while(i < ft_strlen(token_str))
	{
		if (token_str[i] != ' ') 
		{
			start = i;
			while (token_str[i] && token_str[i] != ' ') //serve para quitar os espaços
				i++;
			if (!token->str) //so entra a primeira vez para cada split_token
				token->str = ft_strjoin(pre_dolar, ft_substr(token_str, start, i - start));
			else
			{
				new_token = create_token(token_str, start, i - 1, STRING);
				new_token->next = last_token;
				aux->next = new_token;
				aux = new_token;
			}
		}
		i++;
	}
	return aux; 
}

//hola$a
//hola$a$b$c     -----> hola $a    $b  $c
t_token	*expand2(t_token *token)
{
	int			i;
	int			dolar_position;
	char		*pre_dolar;
	char		*joined;
	t_token		*new_token;
	char		**split = NULL;
	t_token 	*aux;
	t_token 	*last_token; 

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
	printf("pre-dolar: %s\n", pre_dolar);
	token->str = ft_substr(token->str, dolar_position, ft_strlen(token->str) - ft_strlen(pre_dolar));
	
	
	//inicialização
	i = 0;
	new_token = NULL;
	printf("Token a ser expandido: %s\n", token->str);
	split = ft_split(token->str, '$');
	aux = token;
	last_token = token->next;
	token->str = split[0];
	printf("split #%d que deve ser expandido: %s\n", 0, split[0]);
	int j = 1;
	while (split[j]) //$a$b$c => token $a, token $b, token $c
	{
		printf("split #%d que deve ser expandido: %s\n", j, split[j]);
		new_token = create_token_split(split[j]);
		new_token->next = last_token;
		aux->next = new_token;
		aux = new_token;
		j++;
	}
	printf("Lista de tokens recebidos:\n");
	print_list(token);



	//aqui vou tratar o primeiro $a diferente dos $b$c. Vou expandir $a e fazer o join com pre-dolar
	
	token = expand4(token, pre_dolar);
	token = token->next;



	while (token && i < j) //agora vou expandir cada split_token
	{
		last_token = expand3(token);
		token = last_token->next; //ou token = next token do ultimo token expandido
		i++;
	}
	return token;	
}

/*
* Can expand one token into 1 or more tokens.
*/
/* Casos que devem passar
    $a=ls   -la - ok
    $b=     ls    -l    -a    -F    / - ok
    hola$a - ok
    hola$USER$USER -> deve ter o mesmo comportamento de quandao esta entre "": get_expanded_token(token)
	$USER$USER - ok
	$a$a a=ls   -l  -a  -F   <fim> -> ok
	$a$a b -> ok
	$a b -> ok
*/
//return the last token created after the expansion
t_token	*expand_token_int_n_tokens(t_token *token)
{
	if (token->str[0] == '$') //$a$a$a
		return (expand1(token));
	else
		return (expand2(token)); //TODO: hola$a
}