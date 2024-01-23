/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2024/01/23 18:24:45 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* joined serve para juntar varias strings caso estejam "grudadas" 
* ex: echo test > "double"'single'noquote deve juntar as tres palavras
* e criar um output doublesinglenoquote  
*/
t_redirect	*prepare_and_create_redirect(t_token **token)
{
	char	*joined;
	char	*tmp;
	t_type	type;

	joined = NULL;
	type = (*token)->type;
	(*token) = (*token)->next;
	if ((*token)->type == SPC)
		(*token) = (*token)->next;
	while ((*token) && (*token)->str)
	{
		tmp = safe_strjoin(joined, (*token)->str);
		if (joined)
			free(joined);
		joined = tmp;
		(*token) = (*token)->next;
	}
	return (create_redirect(joined, type));
}

/*
* Aqui estamos criando o comando do processo (comando e argumentos)
* e uma lista de redireções, sendo que os comandos e redireções
* são atributos do processo e um não depende do outro para existir. 
* Posso ter um processo com comando, mas sem redireção e vice versa
* ou ter os dois, mas tenhho que ter um ou outro.
* Se durante a criação da lista de redireção aparecer um heredoc, ele
* é executado aqui.
* ---------------------------
* echo hola > f1 - ok
* echo hola > f1 > f2 - ok
* echo hola >> f1 - ok
* echo hola >> f1 >> f2 - ok
* echo hola >> f1 >> f2 >> f3 >> f4 - ok
* echo hola >> f1 > f2 >> f3 > f4 - ok
* echo david      > f1       > f2 - ok
* echo   vaca   >   f1 |   echo patata   > f2 > f3 - ok
* ---------------------------
* Por que usamos um calloc:
* Ou usamos um calloc ou ao um malloc, mas daí temos que setar 
seus valores para NULL (process->next = NULL) para evitar de 
que haja algo em process->next e depois, 	em outro lugar, 
ao verificarmos if (process->next) não passar, ao invés de passar com sujeira
*/
t_process	*create_process(t_token *token, int num_token_str)
{
	int			i;
	t_process	*process;

	i = 0;
	process = create_default_process(num_token_str);
	while (token)
	{
		if (token->str)
			add_word_to_command(&process, &token, i);
		else if (token->type == SPC)
			i = go_to_next_token(&token, process, num_token_str, i);
		else if (token->type == PIPE)
			break ;
		else
			add_redirect(&(process->redirect),
				prepare_and_create_redirect(&token));
	}
	return (process);
}

//Cria-se uma lista de redireções ao criar o processo
//Depois de criar os processos e antes da execução:
//procurar na lista de redireção por 
//heredoc e se tiver executo. Executar um heredoc quer dizer
// entrar no bookle de readline
//depois, na execucao, para cada processo vou executar 
//uma funcao redir(comando)
/*redir(comando) 
{
	while(first_redirec) para cada redireção do comando ...
	{ aqui vou preencher o infile/outfile do processo
		crio o arquivo e retorno o fd (crio o arquivo a depender do tipo de 
				redireção porque um abro com truncate, outro com append ...), 
			se o processo.outfile == -1: processo.outfile = fd criado
			se o processo.outfile != -1: , close (processo.outfile) e 
				processo.outfile = fd criado
		se da algum erro na criacao do arquivo eu retorno o erro e termino
	}
}*/

/*
* Returns: a list of process where each process can have an 
* array of commands and a list of redirections
*/
t_process	*process_creation(t_token *first_token, t_env *env)
{
	int			num_tok_str;
	t_process	*head;
	t_process	*process;
	t_token		*tmp;

	head = NULL;
	process = NULL;
	tmp = NULL;
	while (first_token)
	{
		tmp = first_token;
		num_tok_str = look_for_commands(&first_token);
		process = create_process(tmp, num_tok_str);
		add_process(&head, process);
	}
	if (execute_heredoc(head))
	{
		env->last_exit = 130;
		return (clean_process(&head));
	}
	set_redirects(head);
	return (head);
}
