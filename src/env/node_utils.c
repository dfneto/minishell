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
	t_node *node;

	if (name == NULL)
		return (NULL);
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	return (node);
}