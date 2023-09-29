/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:19:08 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/20 18:35:20 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	free_mem(char **r, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(r[j]);
		j++;
	}
	free(r);
}

static int	set_words(char **r, char const *s, size_t size, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < size - 1)
	{
		while (s[j] == c)
			j++;
		k = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		r[i] = ft_substr(s, k, j - k);
		if (r[i] == NULL)
		{
			free_mem (r, i);
			return (0);
		}
		i++;
	}
	r[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	size_t	words;

	words = count_words(s, c);
	r = (char **) malloc (sizeof(char *) * (words + 1));
	if (r != NULL)
	{
		if (set_words (r, s, words + 1, c))
			return (r);
		else
			return (NULL);
	}
	return (NULL);
}
