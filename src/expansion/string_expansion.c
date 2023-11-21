/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:37 by davifern          #+#    #+#             */
/*   Updated: 2023/11/21 23:56:59 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_after_aux(t_token **aux, t_token *new_token)
{
	(*aux)->next = new_token;
    (*aux) = new_token;
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
	t_token		*next_tok_after_expand;

	new_token = NULL;
	next_tok_after_expand = token->next;
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
				new_token = create_token_with_next(token_str, start, i - 1, STRING, next_tok_after_expand);
				add_token_after_aux(&aux, new_token);
			}
		}
		i++;
	}
	return aux; 
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
	t_token		*next_tok_after_expand;

	new_token = NULL;
	next_tok_after_expand = token->next;
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
				new_token = create_token_with_next(token_str, start, i - 1, STRING, next_tok_after_expand);
				add_token_after_aux(&aux, new_token);
			}
		}
		i++;
	}
	return (aux);
}

//criamos um token para cada dolar existente - 1, ex: $a$b$c -> criamos 2 tokens
//começamos como j=1 porque o j=0 ja foi criado
//return: the amount of token dollars created
int	create_and_add_token_for_each_dollar(char **split, t_token *aux, t_token *next_tok_after_expand)
{
	int			i;
	t_token 	*new_token;

	i = 1;
	new_token = NULL;
	while (split[i]) //$a$b$c => token $a, token $b, token $c
	{
		new_token = create_token_split(split[i], next_tok_after_expand);
		add_token_after_aux(&aux, new_token); //envio &ponteiro quando vou alterar o valor do ponteiro no método chamado e quero o valor atualizado aqui,
		i++;									//se nao quero envio uma copia do ponteiro. Ex: eu quero atualizar o valor de aux a cada
												//while, assim que quero saber seu valor aqui. Então, devo enviar seu endereço. Diferentemente
												//de next_tok_after_expand do qual não será atualizado no método chamado ou new_token que é
												//atualizado e retornado.
		
	}
	return (i);
}

//a $USER$USER a - ok
//a $a$a$a a - ok
t_token	*expand1(t_token *token) //$a$a$a
{
	int			i;
	int			tokens_$_created;
	char		**split;
	t_token		*aux;
	t_token 	*next_tok_after_expand; 

	i = 0;
	split = NULL;
	next_tok_after_expand = token->next;
	aux = token;
	split = ft_split(token->str, '$');
	token->str = split[0]; //reaproveitamos o token atual, mas para isso precisamos alterar seu valor
	
	//crio um token para cada split e adiciono o token criado na sequencia
	tokens_$_created = create_and_add_token_for_each_dollar(split, aux, next_tok_after_expand);
	aux = NULL;
	while (token && i < tokens_$_created) //agora vou expandir cada split_token
	{
		aux = expand3(token);
		token = aux->next; //ou token = next token do ultimo token expandido
		i++;
	}
	return token;
}




// hola$a
// hola$a$b$c     -----> hola $a    $b  $c
t_token	*expand2(t_token *token)
{
	int			i;
	int			dolar_position;
	char		*pre_dolar;
	//char		*joined;
	t_token		*new_token;
	char		**split = NULL;
	t_token 	*aux;
	t_token 	*next_tok_after_expand; 

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	//joined = NULL;
	pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
	printf("pre-dolar: %s\n", pre_dolar);
	token->str = ft_substr(token->str, dolar_position, ft_strlen(token->str) - ft_strlen(pre_dolar));
	
	
	//inicialização
	i = 0;
	new_token = NULL;
	printf("Token a ser expandido: %s\n", token->str);
	split = ft_split(token->str, '$');
	aux = token;
	next_tok_after_expand = token->next;
	token->str = split[0];
	printf("split #%d que deve ser expandido: %s\n", 0, split[0]);
	int j = 1;
	while (split[j]) //$a$b$c => token $a, token $b, token $c
	{
		new_token = create_token_split(split[j++], next_tok_after_expand);
		add_token_after_aux(&aux, new_token);
	}
	printf("Lista de tokens recebidos:\n");
	print_list(token);



	//aqui vou tratar o primeiro $a diferente dos $b$c. Vou expandir $a e fazer o join com pre-dolar
	
	token = expand4(token, pre_dolar);
	token = token->next;



	while (token && i < j - 1) //agora vou expandir cada split_token //entender pq tem que ser j - 1, do contrário da vários erros
	{
		next_tok_after_expand = expand3(token);
		token = next_tok_after_expand->next; //ou token = next token do ultimo token expandido
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