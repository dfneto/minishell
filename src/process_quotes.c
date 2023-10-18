/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:23:46 by davifern          #+#    #+#             */
/*   Updated: 2023/10/18 21:27:46 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *error_msg)
{
	printf("Exiting...\n");
	printf("Error: %s\n", error_msg);
	exit(1);
}

int	is_quote_open(char *input, int *i, char c)
{
	int	open;

	open = 0;
	if (input[*i] == c)
	{
		open = 1;
		while (input[*i] && open)
		{
			(*i)++;
			if (input[*i] == c)
			{
				open = 0;
				break ;
			}
		}
	}
	return (open);
}

int	clean_input(char **input)
{
	free(*input);
	*input = NULL;
	return (1);
}

int	is_exit(char *input)
{
	if (!ft_strncmp(input, "exit", 5))
	{
		printf("Exiting...\n");
		clean_input(&input);
		return (1);
	}
	return (0);
}

/*
* check_open_quotes phase
*/
//TODO: if the last char is a / it should exit with error
int	check_open_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_quote_open(input, &i, 34) || is_quote_open(input, &i, 39))
			exit_error(QUOTE_OPENED);
		i++;
	}
	return (0);
}
