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
    if (*first == NULL)
        *first = new;
	else 
	{
		last = get_last_node(*first);
		last->next = new;
		last = NULL;
	}
}

void	print_type(int type)
{
	if (type == SPACE_TYPE)
		printf("spc\n");
	else if (type == OUTPUT_REDIRECTION_TYPE)
		printf(">\n");
	else if (type == APPEND_TYPE)
		printf(">>\n");
	else if (type == INPUT_REDIRECTION_TYPE)
		printf("<\n");
	else if (type == HERE_DOC_TYPE)
		printf("<<\n");
	else 
		printf("|\n");
}

void	print_list(token *root)
{
	printf("token value:\n");
	while (root)
	{
		if (root->str)
			printf("%s\n", root->str);
		else
			print_type(root->type);
		root = root->next;
	}
}