/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:36:14 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/01/22 16:44:59 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

char	*safe_strjoin(char const *s1, char const *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
	{
		perror("ft_strjoin failed");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

char	*safe_strtrim(char const *s1, char const *set)
{
	char	*ret;

	ret = ft_strtrim(s1, set);
	if (!ret)
	{
		perror("ft_strtrim failed");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

char	*safe_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	ret = ft_substr(s, start, len);
	if (!ret)
	{
		perror("ft_substr failed");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
