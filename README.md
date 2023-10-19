# minishell
TODO:

[ ]  Ler redirections e executing commands e  os demais links para auxiliar meu entendiment
[ ] Eliminar os espaços depois de expandir, mas não sei a ordem do todo (expandir, redirecciones, remover os espacios,  pipes, construir lista de comandos e executar)
	Analisar: 
		echo hola > b adios
		echo hola > c adios > c2 wakawaka
[ ] Implementar o que a Júlia falou de: “ls -la” ser dois tokens quando $a não estiver em “”
[ ] Tenho que abordar $$ ou echo $$?
[ ] Creio que tenho que fazer de $? um token

[ ]  Ver o código do Lucas, assistir os vídeos do CodeVault e ver o pipex
[ ] Em que momento vou tirar os espaços e juntar os tokens, ex: l"s" vira ls?

[ ] Remover quotes
[ ] Compilar o readline no makefile para evitar de ter que instalar em outro computador e poder remover do sgoinfree



[x]  no caso: " $USER abc $PWD d", tenho que expandir somente ou criar tokens e adicionar a lista de tokens? apenas expandir segundo Marc
[x]  fazer a expansão
[x]  bash-3.2$ echo $$$$$USER
















Testes de expansão:
"    $PWD   $USER   a"
0123456789012345678901
         i1         2

"1234$USER#5678$PATH****"
0123456789012345678901234

"1234$USER”
01234567890

"123$USER#456"
012345678901234


Testar:
"123$USER"
"123 $USER"
123$USER
"  $PWD  $USER a"
