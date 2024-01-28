/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:54:37 by davifern          #+#    #+#             */
/*   Updated: 2024/01/28 20:49:18 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * A função create_tok_for_each_dollar é uma pequena aula de
 * quando enviar um ponteiro ou o seu endereço:
 * no add_token_after eu envio &ponteiro quando vou alterar o valor do ponteiro
 * no método chamado e quero o valor atualizado aqui,
 * se nao quero envio uma copia do ponteiro. Ex: eu quero atualizar o valor de
 * aux a cada while, assim que quero saber seu valor aqui. Então, devo enviar
 * seu endereço. Diferentemente de next_tok_after_expand do qual não será
 * atualizado no método chamado ou new_token que é atualizado e retornado.
 */

/* Create and add token for each dollar in token->str
 * criamos um token para cada dolar existente - 1, ex: $a$b$c
	-> criamos 2 tokens:
 * $b e $c porque $a já foi criado e por isso
 * começamos j=1 porque o j=0 ja foi criado
 * return: the amount of token dollars created
 */
int	create_tok_for_each_dollar(char **split, t_token *token, int n)
{
	int		i;
	t_token	*new_token;

	i = n;
	new_token = NULL;
	while (split[i])
	{
		new_token = create_token_split(split[i], token->next);
		add_token_after(&token, new_token);
		i++;
	}
	return (i + (1 - n));
}

/*
* Expand strings with text before $, ex: 123$USER
*/
t_token	*expand_string_pre_dolar(t_token *token, t_env env)
{
	int		toks_dol_created;
	char	*tmp;
	char	**split;

	split = NULL;
	tmp = NULL;
	toks_dol_created = 0;
	tmp = remove_pre_dolar_text(token->str);
	split = safe_split(tmp, '$');
	tmp = ft_free(tmp);
	tmp = g_pre_dol(token->str, 0);
	ft_free(token->str);
	token->str = tmp;
	toks_dol_created = create_tok_for_each_dollar(split, token, 0);
	ft_free(split);
	return (expand_tokens_created(token->next, toks_dol_created - 1, env));
}

/*
* Expand strings that starts with $ and has no text before $, ex: $USER
*/
t_token	*expand_string_no_text(t_token *token, t_env env)
{
	int		toks_dol_created;
	char	**split;

	split = NULL;
	toks_dol_created = 0;
	split = safe_split(token->str, '$');
	token->str = ft_free(token->str);
	token->str = split[0];
	toks_dol_created = create_tok_for_each_dollar(split, token, 1);
	ft_free(split);
	return (expand_tokens_created(token, toks_dol_created, env));
}

/*
 * It also create tokens in case that there are more than one $
 * Case 1: without text before:
 * In the case that you have a token of the form $a$b$c
 * it will split in $a, $b, $c, expand each of them and
 * after the split and expansion will
 * return: the last token created after the expansion
 * ex: export a="ls -la"
 * $a Z-> will return the token SPC
 * (the token before is the 'ls') and
 * token->next = token Z
 * test cases:
 * $a$a$a
 * a $USER$USER a
 * a $a$a$a a
 * Case 2: with text before
 * In the case that you have a token of the form hola$a$b$c
 * it will split in hola$a, $b, $c, expand each of them and
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
	if (token->str[0] == '$')
		return (expand_string_no_text(token, env));
	return (expand_string_pre_dolar(token, env));
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
#some _text$a$b$c

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
t_token	*expand_string_token(t_token *token, t_env env)
{
	t_token	*last_token_expanded;
	char	*tmp;

	last_token_expanded = NULL;
	tmp = NULL;
	if (ft_strcmp(token->str, "$?") == 0)
	{
		tmp = expand_dollar_question(token->str, env);
		token->str = ft_free(token->str);
		token->str = tmp;
		return (token);
	}
	else
		last_token_expanded = expand_tokens(token, env);
	return (last_token_expanded);
}
