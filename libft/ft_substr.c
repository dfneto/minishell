/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:08:56 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/20 16:41:47 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stddef.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	max;
	size_t	size;

	i = 0;
	max = ft_strlen(s);
	if (start >= max)
		size = 1;
	else if (start + len >= max)
		size = max - start + 1;
	else
		size = len + 1;
	sub = (char *) malloc (size);
	if (sub == NULL)
		return (NULL);
	while (i < len && start < max)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub [i] = '\0';
	return (sub);
}
