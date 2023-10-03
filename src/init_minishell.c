#include "minishell.h"


#define QUOTE_OPENED "You have to close your quotes"

int exit_error(char *error_msg)
{
    printf("Exiting...\n");
    printf("Error: %s\n", error_msg);
    return (1);
}

int is_char_open(char *input, int *i, char c)
{
    int open;

    open = 0;
    if (input[*i] == c)
    {
        open = 1;
        while (input[*i] && open)
        {
            (*i)++;
            if (input[*i] == c)
            {
                open = 0;
                break ;
            }
        }
    }
    return (open);
}

int    init_minishell(char **envp)
{
    (void)envp;
    char *input;
    int i;
    
    while (1)
    {
        input = readline("> ");
        if (!input)
            return (0);
        if (!ft_strncmp(input, "exit", 5))
        {
            printf("Exiting...\n");
            free(input);
            input = NULL;           
            break ;
        }
        i = 0;
        while(input[i])
        {
            if (is_char_open(input, &i, 34) || is_char_open(input, &i, 39))
                exit_error(QUOTE_OPENED);
            i++;
        }
        free(input);
        input = NULL;
    }
    rl_clear_history();
    return (1);
}