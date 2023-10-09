#include "minishell.h"

int    init_minishell(char **envp)
{
    (void)envp;
    char *input;
    token *tokens;
    int i;
    
    while (1)
    {
        input = readline("> ");
        printf("%s\n", input);
        if (!input)
            return (0);
        if (is_exit(input))
            break;
        i = 0;
        process_quotes(input);
        tokens = tokenization(input);
        clean_input(&input);
    }
    rl_clear_history();
    return (1);
}