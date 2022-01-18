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
		path = ft_strjoin(paths[i], cmd); // "/usr/bin/ls"
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

	path = find_env_key(all, "PATH"); // "/usr/bin:/bin:/usr/sbin:/sbin:/usr/"
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
	//error처리
}
