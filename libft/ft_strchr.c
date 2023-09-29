/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:46:02 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/11 17:45:13 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	test;

	test = c;
	while (1)
	{
		if (test == *s)
			return ((char *) s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}
