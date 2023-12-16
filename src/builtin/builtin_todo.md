#Builtins

##Echo## #O que deve fazer ? Mostrar texto no terminal## #O que faz no momento ? Mostra texto no terminal## #TO DO
	: Acredito que nada

	##Cd## #O que deve fazer
	? Trocar folder(segundo o subject
					: with only a relative or absolute path)## #O que faz no momento
		? Troca de folder...## #TO DO
		: -Alterar no env o PWD e o OLDPWD
	: a função cd original altera essas variaveis quando troca de pasta.- folder original minishell
		- cd src->muda para folder src - PWD é altearada para minishell / src
		- OLDPWD é alterada para minishell -
		Estou usando getenv que pega do env original e acho que nao deveria ser usado.Criar função "ft_getenv" que pega do nosso env.

		##Pwd## #O que deve fazer
	? Imprimir folder atual## #O que faz no momento ? Imprime folder atual## #TO DO
													: Trocar para ft_getenv e ver erros do panic

		##Export## #O que deve fazer
		? Export sozinho deve imprimir todas as variáveis de ambiente(inclusive as que não tem valor) em ordem alfabética.Export com argumentos deve adicionar
			/ modificar as variaveis correspondentes## #O que faz no momento ? Imprime env em ordem e adiciona variavel de ambiente se tiver valor depois do = Adiciona mais valores se usar o
			+= ## #TO DO :
			-Ver seg fault no caso de export VAR->variavel sem valor deve ser adicionada mas o valor deve ser deixado NULL
			- Revisar casos que falham,
																																																																												as vezes o export repetidamente falha... nao sei pq

	##Unset## #O que deve fazer
	? Remove variaveis de ambiente !## #O que faz no momento ? Remove variaveis de ambiente !## #TO DO
																: Acho que esta ok Testar mais e ver se não é isso que falha o export

	##Env## #O que deve fazer
	? Imprime env na ordem que ele estiver(que para mim parece random...) Só imprime variaveis que tenham valor.## #O que faz no momento ? Imprime todas as variaveis## #TO DO
																																			: acho que esta ok

		##Exit## #O que deve fazer
		? Sair do programa com código que for passado como variável## #O que faz no momento
		? Sair do programa com código que for passado como variável## #TO DO
	: -Ver caso ' 3' e '3 '
		- Exit return value e main faz limpeza OU Exit faz exit e teoricamente limpa toda a memória usada e por isso nao deveria gerar leaks
