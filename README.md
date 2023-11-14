# minishell
DOING
➜  minishell git:(david_branch) ✗ export a="ls       -la"
➜  minishell git:(david_branch) ✗ ./minishell 


br.sh$ ls | $a
token value:
<ls>
spc
|
spc
<ls       -la> ➜ tenho que quebrar em 2 tokens



br.sh$ ls | "$a"➜ quero o valor literal
token value:
<ls>
spc
|
spc
<"ls       -la">

hola$a
token value:
<holals       -la> -> tem que ser: holals -la

TESTAR:
$a$a
"$a$a"

DONE:

[X] https://www.youtube.com/watch?v=5fnVr-zH-SE&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=14
[x] https://www.youtube.com/watch?v=8Q9CPWuRC6o&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=10
[x] implementar o video https://www.youtube.com/watch?v=Mqb2dVRe0uo&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=6
[x] passar as notas do chat para o notion e 
[X] parei na página 24 do manual
[X] NAO TA CLARO PRA MIM REDIRECTION. Ver: videos sobre redirection, codevalue e pipex
[X] passar os highlights do bash para o notion (5.3 Appending Redirected Output (parei aqui no manual))
[x] entender: // this will gonna wait for all the process to finish ---------> PQ???
	while (wait(NULL) != -1 || errno != ECHILD) //TODO: pq imprime 3 vezes e não 2?
[X] https://www.youtube.com/watch?v=94URLRsjqMQ&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=5
[X] vídeos do CodeVault https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=3



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
