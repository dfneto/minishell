#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

void	*safe_malloc(size_t len)
{
	void	*p;

	p = malloc(len);
	if (!p)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	return (p);
}

char	*safe_itoa(int n)
{
    char *ret;

    ret = ft_itoa(n);
    if (!ret)
    {
        perror("ft_itoa failed");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

char	*safe_strdup(const char *s1)
{
    char *ret;

    ret = ft_strdup(s1);
    if (!ret)
    {
        perror("ft_strdup failed");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

void	*safe_calloc(size_t count, size_t size)
{
    void    *p;

    p = ft_calloc(count, size);
    if (!p)
    {
        perror("ft_calloc failed");
        exit(EXIT_FAILURE);
    }
    return (p);
}

char	**safe_split(char const *s, char c)
{
    char **ret;

    ret = ft_split(s, c);
    if (!ret)
    {
        perror("ft_split failed");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

char	*safe_strjoin(char const *s1, char const *s2)
{
    char *ret;

    ret = ft_strjoin(s1, s2);
    if (!ret)
    {
        perror("ft_strjoin failed");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

char	*safe_strtrim(char const *s1, char const *set)
{
    char *ret;

    ret = ft_strtrim(s1, set);
    if (!ret)
    {
        perror("ft_strtrim failed");
        exit(EXIT_FAILURE);
    }
    return (ret);
}

char	*safe_substr(char const *s, unsigned int start, size_t len)
{
    char *ret;

    ret = ft_substr(s, start, len);
    if (!ret)
    {
        perror("ft_substr failed");
        exit(EXIT_FAILURE);
    }
    return (ret);
}





/* 
ft_calloc ok
ft_itoa ok
ft_split ok
ft_strdup ok
ft_strjoin ok
ft_strtrim ok
ft_substr ok
 */
