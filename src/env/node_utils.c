/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:15:18 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/11/23 16:15:53 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clean_node(t_node *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

t_node	*create_node(char *name, char *value)
{
	t_node	*node;

	if (name == NULL)
		return (NULL);
	node = (t_node *)safe_calloc(1, sizeof(t_node));
	node->name = name;
	node->value = value;
	return (node);
}
