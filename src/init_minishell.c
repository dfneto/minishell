#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

void    init_minishell(int *g_signal)
{
    char *input;
    
    input = NULL;
    while (*g_signal)
    {
        input = readline("Brazilian Shell >> ");
        if (!input)
            return ;
        printf("Current signal: %d -> Message received: %s\n", *g_signal, input);
        free(input);
        input = NULL;
    }
}