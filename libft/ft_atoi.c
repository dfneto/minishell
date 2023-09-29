/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:59:11 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/08 13:07:12 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	init_num(const char *str, int *neg)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		*neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	neg;

	res = 0;
	neg = 1;
	i = init_num(str, &neg);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			break ;
		if (ft_isdigit(str[i]))
			res = res * 10 + ((str[i] - '0') * neg);
		i++;
	}
	return (res);
}
