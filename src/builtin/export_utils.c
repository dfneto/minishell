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

int	add_alphabetical(t_node **head, t_node *new_node)
{
	t_node	*current;

	if (!new_node)
		return (1);
	if (*head == NULL || ft_strcmp((*head)->name, new_node->name) >= 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL && ft_strcmp(current->next->name,
				new_node->name) < 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
	return (0);
}

static t_node	*create_ordered_env(t_env env)
{
	t_node	*head;
	t_node	*tmp;

	head = NULL;
	while (env.head)
	{
		if (!env.head->value)
			tmp = create_node(safe_strdup(env.head->name), NULL);
		else
			tmp = create_node(safe_strdup(env.head->name),
					safe_strdup(env.head->value));
		if (add_alphabetical(&head, tmp))
			break ;
		env.head = env.head->next;
	}
	return (head);
}

int	print_ordered(t_env env)
{
	t_node	*ordered;
	t_node	*tmp;

	ordered = create_ordered_env(env);
	if (ordered == NULL)
		return (1);
	while (ordered)
	{
		tmp = ordered;
		printf("declare -x %s", ordered->name);
		if (ordered->value)
			printf("=\"%s\"\n", ordered->value);
		else
			printf("\n");
		ordered = ordered->next;
		clean_node(tmp);
	}
	return (0);
}
