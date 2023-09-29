/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:23:22 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/17 20:01:58 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	look_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*return_empty(void)
{
	char	*r;

	r = (char *) malloc (sizeof(char));
	if (r != NULL)
		r[0] = '\0';
	return (r);
}

static char	*return_trim(char const *s1, size_t i, size_t f)
{
	size_t	j;
	char	*r;

	j = 0;
	r = (char *) malloc (sizeof(char) * (f - i + 2));
	if (r != NULL)
	{
		while (j < f - i + 1)
		{
			r[j] = s1[i + j];
			j++;
		}
		r[j] = '\0';
	}
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	f;

	i = 0;
	f = ft_strlen(s1);
	if (f > 0)
		f--;
	while (look_set(s1[i], set) && i < f)
		i++;
	if (i == f)
		return (return_empty());
	else
	{
		while (look_set(s1[f], set) && f >= i)
			f--;
		return (return_trim(s1, i, f));
	}
}
