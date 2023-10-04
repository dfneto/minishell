#include "minishell.h"

int    init_minishell(char **envp)
{
    (void)envp;
    char *input;
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
        //TODO: por que preciso separar em tokens e não posso ir direto para words (Step 6: Split the command into a command name and arguments.)
        clean_input(&input);
    }
    rl_clear_history();
    return (1);
}