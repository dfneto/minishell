#include "minishell.h"
#include <signal.h>
#include "libft.h"
#include <readline/readline.h>

static void  handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {

    }
    
}

void    init_signals(void)
{
    struct sigaction    act;

    ft_bzero(&act, sizeof(act));
    act.sa_handler = &handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
}