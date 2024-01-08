/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:35:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/10/02 16:36:16 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <libft.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_single_cmd(t_process *process, t_env *env, int last_exit,
		t_builtin functions[])
{
	int		og_stdout;
	int		og_stdin;
	char	*path;

	if (process->outfile == -1 || process->infile == -1)
		return (1);
	set_single_redirects(process, &og_stdin, &og_stdout);
	last_exit = execute_builtins(process->cmd, env, last_exit, functions);
	if (last_exit == -1)
	{
		path = get_path(process->cmd, *env);
		if (path == NULL)
			last_exit = print_cmd_not_found(process->cmd[0]);
		else if (access(path, X_OK))
			last_exit = ft_perror(process->cmd[0], NULL, 127);
		else
			last_exit = do_single_fork(path, process->cmd, *env);
	}
	reset_redirects(process, &og_stdin, &og_stdout);
	return (last_exit);
}