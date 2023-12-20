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

t_node	*create_ordered_env(t_env env)
{
	t_node	*head;
	t_node	*tmp;

	head = NULL;
	while (env.head)
	{
		if (!env.head->value)
			tmp = create_node(ft_strdup(env.head->name), NULL);
		else
			tmp = create_node(ft_strdup(env.head->name),
					ft_strdup(env.head->value));
		if (add_alphabetical(&head, tmp))
			break ;
		env.head = env.head->next;
	}
	return (head);
}

static void	print_ordered(t_env env)
{
	t_node	*ordered;
	t_node	*tmp;

	ordered = create_ordered_env(env);
	if (ordered == NULL)
		return ;
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
}
static int	is_valid_env(char *str)
{
	// printf("%s", str);
	if (!(ft_isalpha(*str) || *str == '_'))
		return (-1);
	str++;
	while (*str && *str != '=' && *str != '+')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (-1);
		str++;
	}
	if (*str == '+')
	{
		str++;
		if (*str == '=')
			return (0);
		return (-1);
	}
	if (*str)
		return (1);
	return (2);
}

/*

 */
int	ft_export(char **argv, t_env *env, int last_exit)
{
	int		ret;
	int		mode;
	size_t	pos;

	(void)last_exit;
	ret = 0;
	argv++;
	if (*argv == NULL)
	{
		print_ordered(*env);
		return (ret);
	}
	while (*argv)
	{
		mode = is_valid_env(*argv);
		printf("mode: %d\n", mode);
		if (mode >= 0)
		{
			// printf("%s\n", *argv);
			if (mode == 1)
			{
				pos = ft_strchr(*argv, '=') - *argv;
				// printf("pos %zus\n", pos);
				ft_setenv(env, ft_substr(*argv, 0, pos), ft_strdup(*argv + pos
						+ 1), mode);
			}
			else if (mode == 0)
			{
				pos = ft_strchr(*argv, '+') - *argv;
				ft_setenv(env, ft_substr(*argv, 0, pos), ft_strdup(*argv + pos
						+ 2), mode);
			}
			else
			{
				ft_setenv(env, *argv, NULL, 0);
			}
		}
		else
		{
			ret = 1;
			print_error("Brazilian Shell: export: `");
			print_error(*argv);
			print_error("\': not a valid identifier\n");
		}
		argv++;
	}
	return (ret);
}
