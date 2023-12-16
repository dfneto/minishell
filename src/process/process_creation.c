/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2023/12/11 21:41:46 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process	*get_last_process(t_process *first)
{
	while (first != NULL && first->next != NULL)
		first = first->next;
	return (first);
}

static void	add_process(t_process **first, t_process *new)
{
	t_process	*last;

	if (!new)
		return ;
	if (*first == NULL)
		*first = new;
	else
	{
		last = get_last_process(*first);
		new->prev = last;
		last->next = new;
		last = NULL;
	}
}

//aqui estamos criando o comando do processo (comando e argumentos) e também as redireções, sendo que os comandos e redireções vao dentro do processo e um não depende do outro para existir. Posso ter comando sem redireção e vice versa ou ter os dois, mas tenhho que ter um ou outro
//echo hola > f1 - ok
//echo hola > f1 > f2 - ok
//echo hola >> f1 - ok
//echo hola >> f1 >> f2 - ok
//echo hola >> f1 >> f2 >> f3 >> f4 - ok
//echo hola >> f1 > f2 >> f3 > f4 - ok
//echo david      > f1       > f2 - ok
//echo   vaca   >   f1 |   echo patata   > f2 > f3 - ok
t_process	*create_process(t_token *token, int num_token_str)
{
	t_process	*process;
	t_redirect 	*redirect;
	t_type			type;
	int			i;

	i = 0;
	type = -1;
	/* ou usa um calloc abaixo ou ao fazer um malloc setar 
	depois seus valores para NULL (process->next = NULL) 
	para evitar de que haja algo em process->next e depois,
	em outro lugar, ao verificarmos if (process->next) não passar,
	ao invés de passar com sujeira
	*/
	process = (t_process *)ft_calloc(1, sizeof(t_process));

	if (process == NULL)
	{
		perror("malloc process");
		exit(EXIT_FAILURE);
	}
	process->next = NULL;
	process->redirect = NULL;
	process->cmd = NULL;
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	if (num_token_str > 0)
	{ 
		process->cmd = (char **)ft_calloc((num_token_str + 1), sizeof(char *));
		if (process->cmd == NULL)
		{
			perror("calloc cmd");
			exit(EXIT_FAILURE);
		}
	}
	while (token)
	{
		if (token->str) //type STR, DOUB ou SING
		{
			process->cmd[i] = ft_strjoin(process->cmd[i], token->str);
			if (process->cmd[i] == NULL)
			{
				perror("ft_strjoin");
				exit(EXIT_FAILURE);
			}
			token = token->next;
		}	
		else if (token->type == SPC)//se encontro um espaço
		{
			token = token->next; //vou para o próximo token
			if (num_token_str > 0) //eu só posso checar abaixo se eu tenho token str.
			{
				if (process->cmd[i]) //e se já tenho algo escrito no comando vou para o próximo comando, assim se a linha começa com um espaço ou tem um espaço depois do pipe eu salto esse espaço mas não mudo de comando
					i++;
			}
		}
		else if (token->type == PIPE)
			break;
		else //aqui crio a lista de redireções
		{
			type = token->type;
			token = token->next;
			if (token->type == SPC)
				token = token->next;
			redirect = create_redirect(token->str, type);
			add_redirect(&(process->redirect), redirect);
			token = token->next;
		}
	}
	//ao termino desse metodo vou ter os comandos, infile e outfile padrão, e uma lista de redirecoes, sendo que se em alguma redirecao tiver um heredoc vou executar este aqui
	
	return (process);
}

//Return the numbers of tokens that have str (DOUBLE, SINGLE QUOTE and STR tokens) per process
int	look_for_commands(t_token **head)
{
	int		num_tok_str;

	num_tok_str = 0;
	while (*head)
	{
		if ((*head)->str)
			num_tok_str++;
		else if ((*head)->type == PIPE)
		{
			*head = (*head)->next;
			break ;
		}
		else if ((*head)->type != SPC)
		{
			while (*head && !(*head)->str)
				*head = (*head)->next;
		}
		*head = (*head)->next;
	}
	return (num_tok_str);
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
		crio o arquivo e retorno o fd (crio o arquivo a depender do tipo de redireção porque um abro com truncate, outro com append ...), 
			se o processo.outfile == -1: processo.outfile = fd criado
			se o processo.outfile != -1: , close (processo.outfile) e processo.outfile = fd criado
		se da algum erro na criacao do arquivo eu retorno o erro e termino
	}
}*/
/*
* return: a list of process where each process can have an 
* array of commands or a list of redirections
*/ 
t_process	*process_creation(t_token *first_token)
{
	t_process	*head;
	t_process	*process;
	t_token		*tmp;
	int			num_tok_str;

	head = NULL;
	process = NULL;
	while (first_token)
	{
		tmp = first_token;
		num_tok_str = look_for_commands(&first_token);
		process = create_process(tmp, num_tok_str);
		add_process(&head, process);
	}
	//ao termino terei uma lista de processos e cada processo com seus comandos e sua lista de redireções
	return (head);
}