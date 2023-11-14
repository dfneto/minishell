#include <libft.h>
#include <unistd.h>

void print_error(char *str)
{
    write(2, str, ft_strlen(str));
}