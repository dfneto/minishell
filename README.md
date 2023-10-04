# minishell

Para compilar:
gcc -g -I inc -I libft -I /sgoinfre/Perso/lsulzbac/homebrew/opt/readline/include -L/sgoinfre/Perso/lsulzbac/homebrew/opt/readline/lib -Llibft -lft -lreadline src/main.c src/init_minishell.c src/utils_quotes.c -o minishell 

[ ] compilar o readline no makefile para evitar de ter que instalar em outro computador e poder remover do sgoinfree