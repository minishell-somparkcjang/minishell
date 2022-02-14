/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:54 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:12:25 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*search_path(char *command, char **paths)
{
	int		i;
	char	*path;
	char	*cmd;
	int		fd;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin("/", command);
		path = ft_strjoin(paths[i], cmd);
		free(cmd);
		fd = open(path, O_RDONLY);
		if (fd > -1)
		{
			close(fd);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

static char	*get_path(t_command *command, t_all *all)
{
	int		i;
	char	**paths;
	char	*path;

	if (ft_strchr(command->command, '/'))
		return (command->command);
	path = find_env_key(all, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	path = search_path(command->command, paths);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (path);
}

void	exec_cmd(t_command *command, t_all *all, char **envp)
{
	char	*path;

	path = get_path(command, all);
	execve(path, command->content, envp);
	error_handler(command->command, errno);
}

void	set_exit(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_exit_code = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_exit_code = 131;
	}
	else
		g_exit_code = WEXITSTATUS(status);
}

void	exec_single_cmd(t_command *command, t_all *all, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		printf("Failed forking child..\n");
	else if (pid == 0)
		exec_cmd(command, all, envp);
	else
	{
		waitpid(pid, &status, 0);
		set_exit(status);
	}
}
