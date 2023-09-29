/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:47:17 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/11 17:54:48 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	to_find;
	int		i;
	int		found;

	to_find = c;
	found = -1;
	i = 0;
	while (1)
	{
		if (to_find == *(s + i))
			found = i;
		if (*(s + i) == '\0')
			break ;
		i++;
	}
	if (found >= 0)
		return ((char *) s + found);
	else
		return (NULL);
}
