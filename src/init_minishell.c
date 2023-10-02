#include "minishell.h"


#define QUOTE_OPENED "You have to close your quotes"

int exit_error(char *error_msg)
{
    printf("Exiting...\n");
    printf("Error: %s\n", error_msg);
    return (1);
}

int    init_minishell(char **envp)
{
    (void)envp;
    char *input;
    int double_quote_open;
    int single_quote_open;
    int i;
    
    double_quote_open = -1;
    single_quote_open = -1;
    input = "wewaea";
    i = 0;
    while (1)
    {
        input = readline("> ");
        // ft_strlcpy(input, "\"\"", 2);
        // input = "wawa";
        if (!input)
            return (0);
        if (!ft_strncmp(input, "exit", 5))
        {
            printf("Exiting...\n");
            free(input);
            input = NULL;           
            break ;
        }
        int open = 0;
        int j = 0;
        //TODO:
        //  “ “ ‘ -> error
        //  “ ‘ “ -> ok
        // echo “david” “Fernandez
        while(input[i])
        {
            if (input[i] == 34)
            {
                j = i + 1;
                open = 1;
                while (input[j])
                {
                    if (input[j] == 34)
                    {
                        open = 0;
                        break ;
                    }
                    j++;
                }
            }
            if (open)
                return (exit_error(QUOTE_OPENED));
            i = j + 1;
        }
        free(input);
        input = NULL;
    }
    rl_clear_history();
    return (1);
}