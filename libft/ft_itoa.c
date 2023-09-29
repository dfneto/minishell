/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:14:41 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/05/16 19:03:39 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		neg;
	char	*r;

	i = get_size(n);
	neg = 1;
	if (n < 0)
		neg = -1;
	r = (char *) malloc (sizeof(char) * (i + 1));
	if (r != NULL)
	{
		r[i] = '\0';
		while (i--)
		{
			r[i] = n % 10 * neg + '0';
			n /= 10;
		}
		if (neg == -1)
			r[0] = '-';
	}
	return (r);
}
