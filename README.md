# minishell

Para compilar en 42:
gcc -g -I inc -I libft -I /sgoinfre/Perso/lsulzbac/homebrew/opt/readline/include -L/sgoinfre/Perso/lsulzbac/homebrew/opt/readline/lib -Llibft -lft -lreadline src/main.c src/init_minishell.c src/utils_quotes.c src/tokenization -o minishell 

Para compilar no meu Mac:
gcc -g -I inc -I /usr/local/opt/readline/include/ -L/usr/local/opt/readline/lib/ -lreadline src/main.c src/init_minishell.c src/utils_quotes.c src/tokenization -o minishell 

[ ] compilar o readline no makefile para evitar de ter que instalar em outro computador e poder remover do sgoinfree