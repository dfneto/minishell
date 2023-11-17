/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:29:55 by davifern          #+#    #+#             */
/*   Updated: 2023/11/10 20:43:02 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_expanded(t_token *token, int *i, int dolar_position)
{
	char	*word_to_expand;

	word_to_expand = NULL;
	while (is_alnum_or_slash(token->str[*i]))
		(*i)++;
	word_to_expand = ft_substr(token->str,
			dolar_position + 1, *i - dolar_position - 1);
	return (getenv(word_to_expand));
}

char	*get_pre_dolar_text(char *str, int *dolar_position, int i)
{
	*dolar_position = get_dolar_position(str, i);
	return (ft_substr(str, i, *dolar_position - i));
}

char	*get_expanded_token(t_token *token)
{
	int		i;
	int		dolar_position;
	char	*pre_dolar;
	char	*joined;

	i = 0;
	dolar_position = 0;
	pre_dolar = NULL;
	joined = NULL;
	while (token->str[i])
	{
		pre_dolar = get_pre_dolar_text(token->str, &dolar_position, i);
		joined = ft_strjoin(joined, pre_dolar);
		i = dolar_position + 1;
		if (token->str[i])
			joined = ft_strjoin(joined,
					get_word_expanded(token, &i, dolar_position));
	}
	return (joined);
}

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

//$USER$USER - ok
//$a$a a=ls   -l  -a  -F   <fim> -> ok
//$a$a b -> ok
//$a b -> ok
//return the last part of the token expanded or the token in case that the expansion is null
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
void	expand1(t_token *token) //$a$a$a
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
	while (split[j])
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
}

void	expand2(t_token *token)
{
	(void) token;	
}

/*
* Can expand one token into 1 or more tokens.
*/
void	expand_token_int_n_tokens(t_token *token)
{
	if (token->str[0] == '$') //$a$a$a
		expand1(token);
	else
		expand2(token); //TODO: hola$a
}

/*
* Can expand one token into 1 or more tokens.
*/
void	_expand_token_int_n_tokens(t_token *token)
{
	int			i;
	int			start;
	char 		*token_str;
	char		**split = NULL;
	t_token 	*aux;
	t_token 	*last_token; 
	t_token 	*new_token;

	//inicialização
	i = 0;
	new_token = NULL;
	
	//pegando pre dolar
	split = ft_split(token->str, '$');
	int j = 0;
	while (split[j])
	{
		
		j++;
	}
	token->str = NULL;
	last_token = token->next;
	if (token->str[0] != '$') //hola$a
		j++;
	while(split[j]) //vou avançando as variveis
	{
		token_str = ft_strdup(getenv(split[j]));
		j++;
		while(token_str[i])
		{
			if (token_str[i] != ' ') 
			{
				start = i;
				while (token_str[i] && token_str[i] != ' ') //serve para quitar os espaços
					i++;
				if (!token->str) //so deve entrar uma vez e para isso devo mudar a condicao
				{
					// se o token original começava com char diferente de $:
						// devo fazer um join da palavra anterior ao dolar (hola) com a primeira palavra depois de expandido (ls)
					// se o token original começava com $:
						token->str = ft_substr(token_str, start, i - start);
				}
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
		

	}
	/*if (split[1] == NULL) //$a
		token_str = ft_strdup(getenv(split[0]));
	else //hola$a
	{
		token_str = ft_strdup(getenv(split[1]));
		pre_dolar = split[0];
	}*/
	
	
	aux = token;
	while(token_str[i])
	{
		if (token_str[i] != ' ') 
		{
			start = i;
			while (token_str[i] && token_str[i] != ' ') //serve para quitar os espaços
				i++;
			if (!token->str) //so entra a primeira vez
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
}

//TODO: primeiro expandir $a=ls   -la - ok
//TODO: expandir $b=     ls    -l    -a    -F    / - ok
//TODO: depois expandir hola$a - ok
//TODO: testar hola$USER$USER -> deve ter o mesmo comportamento de quandao esta entre "": get_expanded_token(token)
void	original_expand_token_int_n_tokens(t_token *token) // removo os espacos, mas nao trato mais de uma variavel, ex: $USER$USER
{
	int			i;
	int			start;
	char 		*token_str;
	char		**split = NULL;
	char		*pre_dolar = NULL;
	t_token 	*aux;
	t_token 	*temp_last; 
	t_token 	*new_token;

	//inicialização
	i = 0;
	new_token = NULL;
	
	//pegando pre dolar
	split = ft_split(token->str, '$');
	if (split[1] == NULL) //$a
		token_str = ft_strdup(getenv(split[0]));
	else //hola$a
	{
		token_str = ft_strdup(getenv(split[1]));
		pre_dolar = split[0];
	}
	
	token->str = NULL;
	aux = token;
	temp_last = token->next;
	while(token_str[i])
	{
		if (token_str[i] != ' ')
		{
			start = i;
			while (token_str[i] && token_str[i] != ' ')
				i++;
			if (!token->str) //so entra a primeira vez
				token->str = ft_strjoin(pre_dolar, ft_substr(token_str, start, i - start));
			else
			{
				new_token = create_token(token_str, start, i - 1, STRING);
				new_token->next = temp_last;
				aux->next = new_token;
				aux = new_token;
			}
		}
		i++;
	}
}

void	expand(t_token *token)
{
	if (token->type == DOUBLE_QUOTE)
		token->str = get_expanded_token(token);
	else
		expand_token_int_n_tokens(token);
}



//TODO: implementar
char	*get_exit_status()
{
	return ("0");
}

int	check_and_expand(t_token *token)
{
	if (is_dollarquestion_mark(token->str))
		token->str = get_exit_status();
	else if (is_expansible(token->str))
		expand(token);
	return (1);
}

int	expansion(t_token *first_token)
{
	while (first_token)
	{
		if (first_token->type == DOUBLE_QUOTE
			|| first_token->type == STRING)
			check_and_expand(first_token);
		first_token = first_token->next;
	}
	return (0);
}
