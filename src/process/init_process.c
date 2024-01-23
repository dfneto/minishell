/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2024/01/23 17:03:47 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char 		* tmp; //Adicionei para arrumar os leaks dos process.txt e process2.txt
	t_process	*process;
	t_redirect	*redirect;
	t_type		type;

	i = 0;
	type = -1;
	process = (t_process *)safe_calloc(1, sizeof(t_process));
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	if (num_token_str > 0)
		process->cmd = (char **)safe_calloc((num_token_str + 1),
				sizeof(char *));
	while (token)
	{
		if (token->str) //type STR, DOUB ou SING
		{
			tmp = safe_strjoin(process->cmd[i], token->str); //Adicionei para arrumar o leak do process2.txt
			if (process->cmd[i])
				free(process->cmd[i]);
			process->cmd[i] = tmp;
			token = token->next;
		}
		else if (token->type == SPC) //se encontro um espaço
		{
			token = token->next; //vou para o próximo token
			if (num_token_str > 0) //eu só posso checar abaixo se eu tenho token str.
			{
				if (process->cmd[i]) //e se já tenho algo escrito no comando vou para o próximo comando, assim se a linha começa com um espaço ou tem um espaço depois do pipe eu salto esse espaço mas não mudo de comando
					i++;
			}
		}
		else if (token->type == PIPE)
			break ;
		else //aqui crio a lista de redireções
		{
			/* Modifiquei aqui para juntar varias strings caso estejam "grudadas" -> ex: echo test > "double"'single'noquote deve juntar as tres palavras e criar um output doublesinglenoquote  */
			char *joined = NULL;
			type = token->type;
			token = token->next;
			if (token->type == SPC)
				token = token->next;
			while (token && token->str)
			{
				tmp = safe_strjoin(joined, token->str); //Adicionei para arrumar o leak do process.txt
				if (joined)
					free(joined);
				joined = tmp;
				token = token->next;
			}
			redirect = create_redirect(joined, type);
			add_redirect(&(process->redirect), redirect);
		}
	}
	return (process);
}



//TODO: criar uma lista de redireções ao criar o processo
//Depois de criar os processos e antes da execução:
//procurar na lista de ao criar a lista de redireção por heredoc e se tiver executo
//executar um heredoc quer dizer entrar no bookle de readline
//depois, na execucao, para cada processo vou executar uma funcao redir(comando)
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
