#include "minishell.h"

int    init_minishell(char **envp)
{
    (void)envp;
    char *input;
    token *first_token;
    int i;
    
    while (1)
    {
        input = readline("\033[38;5;143mbr.sh$ \033[0;39m");
        if (!input)
            return (0);
        if (is_exit(input))
            break;
        i = 0;
        process_quotes(input);
        first_token = tokenization(input);
        // if (!first_token) com esta condicao nao eh permitido inserir nada, nao se pode dar enter por ex que se encerra o programa
        //     return (1);
        clean_input(&input);
    }
    rl_clear_history();
    return (0);
}