#include "minishell.h"

int    init_minishell(char **envp)
{
    (void)envp;
    char *input;
    token *first_token;
    int i;
    
    while (1)
    {
        input = readline("> ");
        if (!input)
            return (0);
        if (is_exit(input))
            break;
        i = 0;
        process_quotes(input);
        first_token = tokenization(input);
        if (!first_token)
            return (1);
        clean_input(&input);
    }
    rl_clear_history();
    return (0);
}