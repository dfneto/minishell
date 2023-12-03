/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:45 by davifern          #+#    #+#             */
/*   Updated: 2023/12/03 16:21:43 by davifern         ###   ########.fr       */
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

t_process	*create_process_L(t_token *token, int num_cmd)
{
	t_process	*process;
	int			i;

	i = 0;
	process = (t_process *)ft_calloc(1, sizeof(t_process));
	if (process == NULL)
	{
		perror("malloc process");
		exit(EXIT_FAILURE);
	}
	process->cmd = (char **)ft_calloc(num_cmd + 1, sizeof(char *));
	if (process->cmd == NULL)
	{
		perror("malloc cmd");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		if (i == num_cmd + 1) //TODO: em que momento isso acontecerá?
		{
			perror("i == num");
			exit(EXIT_FAILURE);
		}
		if (token->str)
		{
			process->cmd[i] = ft_strjoin(process->cmd[i], token->str);
			if (process->cmd[i] == NULL)
			{
				perror("ft_strjoin");
				exit(EXIT_FAILURE);
			}
		}
		else if (token->type == PIPE)
			break ;
		else if (token->type != SPC)
		{
			token = token->next;
			while (token && !token->str)
				token = token->next;
		}
		else if (process->cmd[i] && token->type == SPC)
			i++;
		if (token)
			token = token->next;
	}
	//print_process(process);
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	return (process);
}

//aqui estamos criando o comando do processo (comando e argumentos) e também as redireções
//echo hola > f1 - ok
//echo hola > f1 > f2 - ok
//echo hola >> f1 - ok
//echo hola >> f1 >> f2 - ok
//echo hola >> f1 >> f2 >> f3 >> f4 - ok
//echo hola >> f1 > f2 >> f3 > f4 - ok
//echo david      > f1       > f2 -> apagar os arquivos depois de criados
//echo   vaca   >   f1 |   echo patata   > f2 > f3 
t_process	*create_process(t_token *token, int num_token_str)
{
	t_process	*process;
	t_redirect 	*redirect;
	t_type			type;
	int			i;

	i = 0;
	type = -1;
	process = (t_process *)malloc(sizeof(t_process) + 1);
	if (process == NULL)
	{
		perror("malloc process");
		exit(EXIT_FAILURE);
	}
	process->infile = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	process->cmd = NULL;
	if (num_token_str > 0)
	{
		process->cmd = (char **)malloc((num_token_str + 1) * sizeof(char *));
		if (process->cmd == NULL)
		{
			perror("malloc cmd");
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
	//ao termino desse metodo vou ter os comandos, infile e outfile padrão ou -1, e uma lista de redirecoes, sendo que se em alguma redirecao tiver um heredoc vou executar este aqui
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
		crio o arquivo e retorno o fd (crio o arquivo a depender do tipo de redireção porque um abro com truncate, outro com append ...), 
			se o processo.outfile == -1: processo.outfile = fd criado
			se o processo.outfile != -1: , close (processo.outfile) e processo.outfile = fd criado
		se da algum erro na criacao do arquivo eu retorno o erro e termino
	}
}*/
//depois executo o comando
t_process	*process_creation(t_token *first_token)
{
	t_process	*head;
	t_process	*process;
	t_token		*tmp;
	int			i;

	// int			outfile = STDOUT_FILENO;
	// int			infile = STDIN_FILENO;
	// char		*heredoc;
	head = NULL;
	process = NULL;
	while (first_token)
	{
		tmp = first_token;
		i = 0;
		while (first_token)
		{
			if (first_token->str)
				i++;
			else if (first_token->type == PIPE)
				break ;
			else if (first_token->type != SPC)
			{
				while (first_token && !first_token->str)
					first_token = first_token->next;
			}
			first_token = first_token->next;
		}
		// printf("tenho %d token str\n", i);
		if (i >= 0)
		{
			process = create_process(tmp, i); //i eh o numero de token str que tenho, tmp é o primeiro token
			add_process(&head, process);
			// print_process(process);
		}
		else if (first_token) //wip: mudar a logica para fazer isso no caso de ser pipe
			first_token = first_token->next;
	}
	//ao termino terei uma lista de processos e cada processo com seus comandos e sua lista de redireções
	return (head);
}