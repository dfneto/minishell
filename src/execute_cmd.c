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

int	is_builtin(char *exec)
{
	int	i;

	char *builtins[] = {"echo", "pwd", "exit", "env", "cd", NULL};
	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(exec, builtins[i], ft_strlen(exec) + 1))
			return (i);
		i++;
	}
	return (-1);
}

void	clean_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

char	*get_path(char **cmd)
{
	char	*abs_path;
	char	**paths;
	int		i;

	i = 0;
	abs_path = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!abs_path)
		return (NULL);
	ft_strlcat(abs_path, cmd[0], PATH_MAX);
	if (!access(abs_path, X_OK))
		return (abs_path);
	paths = ft_split(getenv("PATH"), ':');
	if (paths)
	{
		while (paths[i])
		{
			ft_bzero(abs_path, PATH_MAX);
			ft_strlcpy(abs_path, paths[i], ft_strlen(paths[i]) + 1);
			ft_strlcat(abs_path, "/", PATH_MAX);
			ft_strlcat(abs_path, cmd[0], PATH_MAX);
			printf("%s\n", abs_path);
			if (!access(abs_path, X_OK))
			{
				clean_array(paths);
				return (abs_path);
			}
			i++;
		}
	}
	clean_array(paths);
	free(abs_path);
	return (NULL);
}

int	is_executable(char **cmd, char **envp)
{
	int		ret;
	char	*path;

	path = get_path(cmd);
	printf("Get_path = %s\n", path);
	if (path == NULL)
		return (127);
	ret = fork();
	if (ret == 0)
		execve(path, cmd, envp);
	else
	{
		free(path);
		wait(&ret);
	}
	return (ret);
}

void	execute_cmd(t_process *current_process, char **envp)
{
	int	ret;
	int	is_built;

	is_built = is_builtin(current_process->cmd[0]);
	ret = 0;
	if (is_built < 0)
	{
		ret = is_executable(current_process->cmd, envp);
	}
	else
	{
		printf("Is built in!!\n");
		if (is_built == 0)
			ft_echo(current_process->cmd);
		else if (is_built == 1)
			ft_pwd();
		else if (is_built == 2)
			ft_exit();
		else if (is_built == 3)
			ft_env(envp);
		else if (is_built == 4)
			ft_cd(current_process->cmd);
	}
	if (ret)
	{
		printf("Brazilian Shell: %s: command not found\n",
			current_process->cmd[0]);
	}
}
