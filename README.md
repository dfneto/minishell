# minishell

## TO DO

### Task 1

Refactor
No arquivo expansio devo refatorar os métodos expand:
1->3 //caso $a$b$c
2->4,3 //caso hola$a$b$c
O 2 eh uma copia alterada do 1 e o 4 alterada do 3, sendo que no método 2 eh chamado o metodo 4 para um caso de hola$a e o 3 para $b$c (no caos de token hola$a$b$c)

echo "$USER$USER" -> deve printar sem aspas

### Task 2

Organizar makefile  

### Task 3 - Lucas

Refactor all (refatorar a partir do execute command para o David poder alterar - colocar comentarios TODO para o david ou lucas fazerem depois)  
Verificar quais builtins faltam e [criar tarefas](https://github.com/dfneto/minishell/blob/main/src/builtin/builtin_todo.md)    

### Task 4 - ______

Sinais

### Task 5 - David

Redirect && heredoc 

### Task 6 - Lucas

Executavel precisa ./ ????  
Execve executa arquivos baseados na pasta que ele esta e nao necessita ./  

Ex.: dentro do minishell o comando minishell funciona, no bash necessita ./minishell  

É necessario essa merda?  

### Task 7

Struct env? Array env? Ó duvida cruel!  

### Task 8

Colocar a lib readline dentro do projeto (A REFLETIR)


### Task 9
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


### Task 10

LEAKSSSSSSS!
