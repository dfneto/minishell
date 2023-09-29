/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:53:17 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/17 18:08:13 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	size_t	i;

	i = 0;
	r = (char *) malloc (ft_strlen(s) + 1);
	if (r != NULL)
	{
		while (s[i] != '\0')
		{
			r[i] = (*f)(i, s[i]);
			i++;
		}
		r[i] = '\0';
	}
	return (r);
}
