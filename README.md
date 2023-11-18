# minishell

No arquivo expansio devo refatorar os métodos expand:
1->3 //caso $a$b$c
2->4,3 //caso hola$a$b$c
O 2 eh uma copia alterada do 1 e o 4 alterada do 3, sendo que no método 2 eh chamado o metodo 4 para um caso de hola$a e o 3 para $b$c (no caos de token hola$a$b$c)
