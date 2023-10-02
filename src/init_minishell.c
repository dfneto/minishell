#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void    init_minishell(char **envp)
{
    char *input;
    t_process *process;
    
    input = NULL;
    while (1)
    {
        input = readline("Brazilian Shell ~~> ");
        if (!input)
            return ;
        if (input[0] != '\0')
        {
            add_history(input);
            process = create_process(input);
            execute_cmd(process, envp);
            clean_process(process);
        }
        free(input);
        input = NULL;
    }
    rl_clear_history();
}