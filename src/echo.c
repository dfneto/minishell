#include <stdio.h>
#include <libft.h>

static void print_args(int argc, char **argv)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    if (!ft_strncmp(argv[i], "-n", 3))
    {
        new_line = 0;
        i++;
    }
    while (i < argc)
    {
        printf("%s", argv[i]);
        if (new_line)
            printf("\n");
        else if (i < argc - 1)
            printf(" ");
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
        printf("\n");
    else
        print_args(argc, argv);
    return (0);
}