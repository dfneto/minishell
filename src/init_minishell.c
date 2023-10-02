#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>


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
    input = NULL;
    i = 0;
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
        
        while(input[i])
        {
            if (input[i] == 34) //" 34
                double_quote_open *= -1;
            if (input[i] == 39)//' 39
                single_quote_open *= -1;
            i++;
        }
        if (double_quote_open == 1 || single_quote_open == 1)
            return (exit_error(QUOTE_OPENED));
        double_quote_open = -1;
        single_quote_open = -1;
        free(input);
        input = NULL;
    }
    rl_clear_history();
    return (1);
}