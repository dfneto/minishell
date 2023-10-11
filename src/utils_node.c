#include "minishell.h"

token	*get_last_node(token *first)
{
	while (first != NULL && first->next != NULL)
		first = first->next;
	return (first);
}

void	add_node_back(token **first, token *new)
{
	token	*last;

    if (!new)
		return ; //TODO: simular new = NULL
    if (!(*first))
        *first = new;
	last = get_last_node(*first);
	last->next = new;
	last = NULL;
}