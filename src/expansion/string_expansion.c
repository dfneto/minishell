/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:37 by davifern          #+#    #+#             */
/*   Updated: 2024/01/22 17:50:41 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* Pequena aula de quando enviar um ponteiro ou o seu endereço:
* no add_token_after eu envio &ponteiro quando vou alterar o valor do ponteiro
* no método chamado e quero o valor atualizado aqui,
* se nao quero envio uma copia do ponteiro. Ex: eu quero atualizar o valor de 
* aux a cada while, assim que quero saber seu valor aqui. Então, devo enviar 
* seu endereço. Diferentemente de next_tok_after_expand do qual não será 
* atualizado no método chamado ou new_token que é atualizado e retornado.
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
	t_token		*new_token;

	if (a == 1)
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

/*
* It also create tokens in case that there are more than one $
* Case 1: without text before: 
* In the case that you have a token of the form $a$b$c
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
* Case 2: with text before
* In the case that you have a token of the form hola$a$b$c
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
* obs: we reuse the actual token and we set its value to the text before the 
* dollar or to the first expansion, in case that the token has not pre text
*/
t_token	*expand_tokens(t_token *token, t_env env)
{
	int			toks_dol_created;
	char		**split;
	t_token		*aux;
	t_token		*next_tok_after_expand;

	split = NULL;
	next_tok_after_expand = token->next;
	aux = token;
	toks_dol_created = 0;
	if (token->str[0] == '$')
	{
		split = safe_split(token->str, '$');
		token->str = split[0];
		toks_dol_created = create_and_add_token_for_each_dollar(split, aux, next_tok_after_expand, 1);
		return (expand_tokens_created(token, toks_dol_created, env));
	}
	else
	{
		split = safe_split(remove_pre_dolar_text(token->str), '$');
		token->str = g_pre_dol(token->str, 0);
		toks_dol_created = create_and_add_token_for_each_dollar(split, aux, next_tok_after_expand, 0);
		return (expand_tokens_created(token->next, toks_dol_created - 1, env));
	}
}

/*
* TODO: tratar $? quando tem texto ou variáveis de ambiente antes e 
* depois, ex: echo $USER $? $USER (OK), echo $USER$?$USER (KO),
* echo $USER$? (KO), echo $USER $?$USER (KO), echo $?$USER (KO), echo $USER$?
* Como ta implementado só funciona se o token for $?
* ----------------------------------------
* Expand one token into 1 or more tokens.
* return: the last token created after the expansion
* There are 2 cases to expand:
* $a$b$c
# some_text$a$b$c
* In case that the token expanded has spaces, the expansion
* is tranformed in n tokens.
* Exs:
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
	if (ft_strcmp(token->str, "$?") == 0)
	{
		token->str = expand_dollar_question(token->str, env);
		return (token);
	}
	else
		last_token_expanded = expand_tokens(token, env);
	return (last_token_expanded);
}