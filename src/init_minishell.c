#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void    init_minishell(char **envp)
{
    char *input;
    char **argv;
    int     ret;
    
    input = NULL;
    while (1)
    {
        input = readline("Brazilian Shell >> ");
        if (!input)
            return ;
        if (!ft_strncmp(input, "exit", 5))
        {
            printf("Exiting...\n");
            free(input);
            input = NULL;           
            break ;
        }
        if (input[0] != '\0')
        {
            add_history(input);
            argv = ft_split(input, ' ');
            ret = fork();
            if (ret == 0)
            {
                execve(argv[0], argv, envp);
                break ;
            }
            else
            {
                wait(NULL);
            }
            printf("Message received: %s\n", input);
        }
        free(input);
        input = NULL;
    }
    rl_clear_history();
}