/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:37 by davifern          #+#    #+#             */
/*   Updated: 2024/01/21 17:29:06 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_space(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

/*
* Receive a token starting by $. Ex: $a
* Return: the last part of the token expanded or the token in the 
* case that the expansion is null
* ex: a="ls   -l    -a  -F   " 
* $a patata: returns the token -F with token->next = patata
*/
t_token	*expand_token_dolar(t_token *token, t_env env)
{
	char		*expanded_str;
	t_token		*next_tok_after_expand;

	next_tok_after_expand = token->next;

	//ADICIONEI ESSE TESTE PARA EVITAR DE CRIAR O TOKEN QUANDO A VARIAVEL NAO EXISTE NO ENV
	if (!exist_in_env(token->str, env))
	{
		token->str = NULL;
		token->type = SPC;
		return (token);
	}
	if (token->str == NULL)
		expanded_str = safe_strdup("");
	else
		expanded_str = safe_strdup(ft_getenv(token->str, env));
	//if (expanded_str == NULL)     -> RETIREI ESSA PARTE PORQUE O SAFE STRDUP NUNCA VAI RETORNAR NULL!
	//	return (set_token_str(token, ""));
	token->str = NULL;
	if (has_space(expanded_str))
		return (create_tok_per_word_in(expanded_str, next_tok_after_expand, token));
	else //TODO: talvez deva alterar o compartamento de quando a string expandida (ex: $USER -> david) não tenha espaço para se 
	{	//assemelhar ao caso em que tem espaço, ou não tbm. Porque se eu tenhoo que token->str tem um valor diferente de nulo tbm da erro de segfault
		token->str = expanded_str;
		return (token);
	}
}

/* 
* Pequena aula de quando enviar um ponteiro ou o seu endereço:
* no add_token_after eu envio &ponteiro quando vou alterar o valor do ponteiro no método chamado e quero o valor atualizado aqui,
* se nao quero envio uma copia do ponteiro. Ex: eu quero atualizar o valor de aux a cada
* while, assim que quero saber seu valor aqui. Então, devo enviar seu endereço. Diferentemente
* de next_tok_after_expand do qual não será atualizado no método chamado ou new_token que é
* atualizado e retornado.
*/
/*
* criamos um token para cada dolar existente - 1, ex: $a$b$c -> criamos 2 tokens:
* $b e $c porque $a já foi criado e por isso
* começamos j=1 porque o j=0 ja foi criado
* return: the amount of token dollars created
*/
int	create_and_add_token_for_each_dollar(char **split, t_token *aux, t_token *next_tok_after_expand, int a)
{
	int			i;
	t_token 	*new_token;

	if (a == 1) //TODO: melhorar essa nojeira!
	{
		i = 1;
		new_token = NULL;
		while (split[i])
		{
			new_token = create_token_split(split[i], next_tok_after_expand);
			add_token_after(&aux, new_token); 
			i++;
			
		}
		return (i);
	}
	else //a == 0
	{
		i = 0;
		new_token = NULL;
		while (split[i])
		{
			new_token = create_token_split(split[i], next_tok_after_expand);
			add_token_after(&aux, new_token); 
			i++;
			
		}
		return (i + 1);
	}
}

/* In the case that you have a token of the form $a$b$c
* it will split in $a, $b, $c, expand each of them and
* after the split and expansion will
* return: the last token created after the expansion
* ex: export a="ls -la"
* $a Z-> will return the token->str=-la 
* (the token before is the 'ls') and  
* token->next = token Z 
* test cases:
* $a$a$a
* a $USER$USER a
* a $a$a$a a
*/
t_token	*expand_tok_withOUT_text_before(t_token *token, t_env env)
{
	int			i;
	int			tokens_$_created;
	char		**split;
	t_token		*aux;
	t_token 	*next_tok_after_expand; 

	/* RELATED TO PRE DOLAR TEXT */
	// int			dolar_position;
	// char		*pre_dolar;
	
	i = 0;
	split = NULL;
	next_tok_after_expand = token->next;
	aux = token;
	tokens_$_created = 0;

	//isso ficaria melhor fora deste método
	if (is_dollarquestion_mark(token->str))
	{
		token->str = safe_strdup(get_exit_status());
		return (token);
	}
	
	/* DO THINGS IN CASE OF TEXT PRE DOLAR */
// 	pre_dolar = NULL;
// 	dolar_position = 0;
// 	pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
// 	char *str_without_pre_dolar_text = remove_pre_dolar_text(token->str, dolar_position);
	
	//fazemos o split
	split = safe_split(token->str, '$');
	//reaproveitamos o token atual, mas para isso precisamos alterar seu valor
	token->str = split[0]; 


	tokens_$_created = create_and_add_token_for_each_dollar(split, aux, next_tok_after_expand, 1);
	aux = NULL;
	
	//agora vou expandir cada token_$ criado
	while (token && i < tokens_$_created) 
	{
		aux = expand_token_dolar(token, env);
		token = aux->next; 
		i++;
	}
	return token;
}

/* In the case that you have a token of the form hola$a$b$c
* it will split in hola$a, $b, $c, expand eacch of them and
* after the split and expansion will
* return: the last token created after the expansion
* ex: export a="ls -la"
* hola$a Z-> will return the token->str=-la 
* (the token before is the 'holals') and 
* token->next = token Z 
* test cases:
* hola$a b
* hola$a$a$a b
* hola$USER$USER b
*/
t_token	*expand_tok_with_text_before(t_token *token, t_env env)
{
	int			i;
	int			tokens_$_created;
	char		**split;
	t_token 	*aux;
	t_token 	*next_tok_after_expand; 
	
	/* RELATED TO PRE DOLAR TEXT */
	int			dolar_position;
	char		*pre_dolar;

	i = 0;
	split = NULL;
	next_tok_after_expand = token->next;
	aux = token;
	tokens_$_created = 0;
	
	/* DO THINGS IN CASE OF TEXT PRE DOLAR */
	pre_dolar = NULL;
	dolar_position = 0;
	pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
	char *str_without_pre_dolar_text = remove_pre_dolar_text(token->str, dolar_position);
	
	//fazemos o split
	split = safe_split(str_without_pre_dolar_text, '$');
	//reaproveitamos o token atual, mas para isso precisamos alterar seu valor
	token->str = pre_dolar;

	tokens_$_created = create_and_add_token_for_each_dollar(split, aux, next_tok_after_expand, 0);
	aux = NULL;

	token = token->next;
	//TODO: refatorar o expand_token_dolar e demais métodos para remover o pre_dolar
	//aqui vou tratar o primeiro $a diferente dos $b$c. Vou expandir $a e fazer o join com pre-dolar
	// token = expand_token_dolar(token, pre_dolar);
	

	//agora vou expandir cada split_token
	while (token && i < tokens_$_created - 1) //entender pq tem que ser j - 1, do contrário da vários erros
	{
		aux = expand_token_dolar(token, env);
		token = aux->next; 
		i++;
	}
	return token;	
}

/*
* Expand one token into 1 or more tokens.
* return: the last token created after the expansion
* There are 2 cases to expand:
* $a$b$c
# some_text$a$b$c
* Ex:
*	$a="ls   -la" -> tokens: ls, -la
*   $b="    ls    -l    -a    -F    " -> tokens: ls, -l -a, -F
*   hola$a -> tokens: holals, -la
*   hola$USER$USER -> token: holadaviferndaviferndavifern
*	$USER$USER - ok
*	$b$b Z > -> tokens: ls, -l -a, -F, Z
*	$a$a Z -> tokens: ls, -la, ls -la, Z
*	$a Z -> tokens: ls, -la, Z
*/
t_token	*expand_token_int_n_tokens(t_token *token, t_env env)
{
	t_token	*last_token_expanded;

	last_token_expanded = NULL;
	//TODO: tratar $? quando tem texto ou variáveis de ambiente antes e depois
	if (token->str[0] == '$')
		last_token_expanded = expand_tok_withOUT_text_before(token, env);
	else
		last_token_expanded = expand_tok_with_text_before(token, env);
	return (last_token_expanded);
}