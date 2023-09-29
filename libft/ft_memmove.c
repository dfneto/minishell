/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:12:35 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/13 20:20:35 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((dst != NULL) | (src != NULL))
	{
		if (dst < src)
			return (ft_memcpy(dst, src, len));
		else
		{
			while (len--)
			{
				*(char *)(dst + len) = *(char *)(src + len);
			}
		}
	}
	return (dst);
}
