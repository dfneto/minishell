# minishell

## TO DO

- David: 5, 4
- Lucas: 3, 4

### Task 2 - MAKEFILE [___]

Organizar makefile  

### Task 3 - BUILTINS [ESS]

Refactor all (refatorar a partir do execute command para o David poder alterar - colocar comentarios TODO para o david ou lucas fazerem depois)  
Verificar quais builtins faltam e [criar tarefas](https://github.com/dfneto/minishell/blob/main/src/builtin/builtin_todo.md)    

### Task 4 - SINAIS [ESS]

Sinais

### Task 5 - REDIRECTS [ESS]

Redirect && heredoc 
Meu objetivo é fazer até sexta uma lista de redireções por processo e o heredoc e deixar pro mr Juppi fazer a execucação das redireções (lembrando que pode ter várias e ainda os pipes)
Daí no sábado e domingo faria os sinais e o sr Juppi o resto que faltava ;)


### Task 8 - READLINE [___]

Colocar a lib readline dentro do projeto (A REFLETIR)

### Task 15 - $"USER" [___]
Testar:
$"USER"
bash: USER: command not found -> correto  
$

### Task 19 - Leaks ou algo mais? [___]

Leaks aparentemente estāo ok, mas o programa leaks trava em alguns comandos...  
Ex.:  
cmd_not_exist  
echo test | wc  

Será que tem leaks nesses comandos? E por que o leaks trava?

## DONE


### Task 1 - OK

Refactor
No arquivo expansio devo refatorar os métodos expand:
1->3 //caso $a$b$c
2->4,3 //caso hola$a$b$c
O 2 eh uma copia alterada do 1 e o 4 alterada do 3, sendo que no método 2 eh chamado o metodo 4 para um caso de hola$a e o 3 para $b$c (no caos de token hola$a$b$c)

### Task 6 - Lucas - Aparentemente ok

Executavel precisa ./ ????  
Execve executa arquivos baseados na pasta que ele esta e nao necessita ./  

Ex.: dentro do minishell o comando minishell funciona, no bash necessita ./minishell  

É necessario essa merda?  

### Task 7

Struct env? Array env? Ó duvida cruel!  
STRUCT ENV FOI O VENCEDOR!  


### Task 9 - OK
Na criacao do processo juntar tokens que nao tenham espaco entre eles.
echo $USER$USER -> deve printar sem espaço
Ex: echo $USER$USER$USER deve retornar dois tokens: echo e lsulzbaclsulzbaclsulzbac
Ex:
echo $a$a$a
<echo>
<ls>
<-la>
<ls>
<-la>
<ls>
<-la>
Na verdade deve retornar
<echo>
<ls> 
<-lals>
<-lals>
<-la>

Testar:
bash-3.2$ export a="    ls    -la   "
bash-3.2$ echo$a
ls -la
bash-3.2$ echo$USER
bash: echodavifern: command not found
bash-3.2$ export b="ls -la"
bash-3.2$ echo$b
bash: echols: command not found


### Task 12 - BUGS - OK
Resolver: OK!!!
testar $z, hola$z quando z eh uma variável não existente em env

Resolver:
Criar um token espaço para quando houver n espaços

Resolver:
export a="  ls   -l   -a  -F   "
export b="ls   -la  "

hola$a
bash: hola: command not found

hola$b
bash: holals: command not found  

### Task 13 - BUGS
Quando digito espaço somente no minishell da segfault  


### Task 14 - Tirar aspas - OK
echo "$USER$USER" -> deve printar sem aspas
testar hola$USER$USER$USER
export a="  ls   -l   -a  -F   "
testar hola $a $USER $USER (uma vez me deu segfault e depois não mais)  

### Task 11 - FT_GETENV [ESS] - 1 Lucas
Alterar todas as expansões para usar a ft_getenv e avisar ao David  

### Task 18 - FT_ENV TO ARR [ESS]

- transformar ft_env em array para enviar para execve  


### Task 17 - FUNCIONAMENTO DO "" [___]

- Bash: 
bash-3.2$ ""  
bash: : command not found  
- Minishell: nao faz nada xD  



### Task 16 - VALIDATE TOKEN [ESS]

|ls  
Makefile                README.md               dep       
$> < | ls$  
Makefile                README.md               dep   

quando não deveria:  
bash-3.2$ > < |ls  
bash: syntax error near unexpected token `<'  
bash-3.2$ > < | ls  
bash: syntax error near unexpected token `<'  
bash-3.2$  > < | ls  
bash: syntax error near unexpected token `<'  
bash-3.2$   | ls  
bash: syntax error near unexpected token `|'  
bash-3.2$   | ls  
bash: syntax error near unexpected token `|'  

### Task 18 - SEFFAULT [ESS]
br.sh$ >f1
Imprimindo as redireções ...
redirect: > - file name: f1
[1]    9120 segmentation fault  ./minishell 

### Task 10 - LEAKS [ESS]

LEAKSSSSSSS de tokens e de processos  
