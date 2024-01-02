/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:35:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/12/16 12:05:25 by lsulzbac         ###   ########.fr       */
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

static int	is_cmd_executable(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

static void	get_abs_path(char **abs_path, char *path, char *cmd)
{
	ft_bzero(*abs_path, PATH_MAX);
	ft_strlcpy(*abs_path, path, ft_strlen(path) + 1);
	ft_strlcat(*abs_path, "/", PATH_MAX);
	ft_strlcat(*abs_path, cmd, PATH_MAX);
}

static char	*return_path(char *abs_path, char *paths)
{
	if (abs_path && !paths)
	{
		free(abs_path);
		return (NULL);
	}
	if (abs_path && paths)
	{
		free(paths);
		return (abs_path);
	}
	return (NULL);
}

char	*get_path(char **cmd, t_env env)
{
	char	*abs_path;
	char	*paths;
	char	*path;

	if (cmd[0][0] == '\0')
		return (NULL);
	if (is_cmd_executable(cmd[0]) || !ft_getenv("PATH", env))
		return (ft_strdup(cmd[0]));
	abs_path = (char *)ft_calloc(PATH_MAX, sizeof(char));
	if (!abs_path)
		return (NULL);
	paths = ft_strdup(ft_getenv("PATH", env));
	if (!paths)
		return (return_path(abs_path, paths));
	path = ft_strtok(paths, ":");
	while (path)
	{
		get_abs_path(&abs_path, path, cmd[0]);
		if (!access(abs_path, X_OK))
			return (return_path(abs_path, paths));
		path = ft_strtok(NULL, ":");
	}
	free(abs_path);
	return (NULL);
}

void	close_pipes(int pipe[])
{
	close(pipe[0]);
	close(pipe[1]);
}
