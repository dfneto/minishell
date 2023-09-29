/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:53:47 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/16 14:06:23 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*r;
	size_t	size;

	size = ft_strlen(s1);
	r = (char *) malloc (size + 1);
	if (r != NULL)
	{
		r[size] = '\0';
		while (size--)
			r[size] = s1[size];
	}
	return (r);
}
