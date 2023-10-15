# minishell

[ ] ler o bash e seguir com a fase process_creation
[ ] em que momento vou tirar os espaços e juntar os tokens, ex: l"s" vira ls?
[X] no caso: "  $USER  abc  $PWD  d", tenho que expandir somente ou criar tokens e adicionar a lista de tokens? apenas expandir segundo Marc
[ ] fazer a expansão e depois criar uma lista de processos
[X] bash-3.2$ echo $$$$$USER
[ ] compilar o readline no makefile para evitar de ter que instalar em outro computador e poder remover do sgoinfree
[ ] Implementar usando lista de tokens e depois usar uma AST para o bônus

Para compilar en 42:
gcc -g -I inc -I libft -I /sgoinfre/Perso/lsulzbac/homebrew/opt/readline/include -L/sgoinfre/Perso/lsulzbac/homebrew/opt/readline/lib -Llibft -lft -lreadline src/create_tokens.c src/lexical_analysis.c src/printers.c src/utils_token.c src/init_minishell.c src/main.c src/utils_quotes.c -o minishell 

Para compilar no meu Mac:
gcc -g -I inc -I libft -I /usr/local/opt/readline/include/ -L/usr/local/opt/readline/lib/ -Llibft -lft -lreadline src/create_tokens.c src/lexical_analysis.c src/printers.c src/utils_token.c src/init_minishell.c src/main.c src/utils_quotes.c -o minishell 
