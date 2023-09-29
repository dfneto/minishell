#include "minishell.h"
#include <signal.h>
#include "libft.h"

int g_signal = 1;

static void  handler(int signal)
{
    if (signal == SIGINT)
        g_signal = 2;
    if (signal == SIGQUIT)
        g_signal = 3;
}

int    *init_signals(void)
{
    struct sigaction    act;

    ft_bzero(&act, sizeof(act));
    act.sa_handler = &handler;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    return (&g_signal);
}