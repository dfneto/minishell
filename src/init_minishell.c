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


void    init_minishell(char **envp)
{
    char *input;
    char *folder;
    char **argv;
    int     ret;
    
    input = NULL;
    folder = (char *) malloc (sizeof(char) * PATH_MAX); //MALLOC NOT PROTECTED
    while (1)
    {
        folder = getcwd(folder, PATH_MAX);
        folder = ft_strrchr(folder, '/');
        folder++;
        ft_strlcat(folder, " % ", ft_strlen(folder) + 4);
        input = readline(folder);
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
                if (execve(argv[0], argv, envp) == -1)
                {
                    printf("EXECVE FAILED - %d!\n", errno);
                    errno = 0;
                    printf("ERRNO RESET - %d!\n", errno);
                }
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