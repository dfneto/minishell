/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:07 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:25:38 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

/* static t_env *add_in_order(t_env *ordered, t_env node)
{
	node.next = NULL;
	if (ordered == NULL)
	{
		ordered
	}
}

static void	print_ordered(t_env *env)
{
	t_env	*ordered;

	ordered = NULL;
	while (env)
	{
		ordered = add_in_order(ordered, *env);
		env = env->next;
	}
}
 */
/* static int	is_valid_env(char c)
{
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c == '_'))
		return (1);
	return (0);
}

int	ft_export(char **str, t_env **env)
{
	if (*str == NULL)
	{
		print_ordered(*env);
		return (0);
	}
	while (*str)
	{
		if (is_valid_env((*str)[0]))
		{
			*env = add_node(create_node(*str), *env);
		}
		str++;
	}
	return (0);
} */
