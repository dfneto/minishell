/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:31:14 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/18 20:48:33 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	i = 0;
	r = (char *) malloc (s1_len + ft_strlen(s2) + 1);
	if (r != NULL)
	{
		while (s1 && s1[i])
		{
			r[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2 && s2[i])
		{
			r[i + s1_len] = s2[i];
			i++;
		}
		r[i + s1_len] = '\0';
	}
	return (r);
}
