#include "../include/minishell.h"

static char	*find_newpath(char *path, t_all *all)
{
	if (*path == '~')
		return (ft_strdup(find_env_key(all, "HOME")));
	else
		return (ft_strdup(path));
}

void	ms_cd(char **content, t_all *all)
{
	char	*oldpath;
	char	*newpath;

	if (content[1] == NULL)
		newpath = ft_strdup(find_env_key(all, "HOME"));
	else
		newpath = find_newpath(content[1], all);
	oldpath = getcwd(NULL, 0);
	if (!oldpath || !newpath)
	{
		free(newpath);
		free(oldpath);
		all->exit_code = 1;
		return ;
	}
	if (chdir(newpath) == -1)
	{
		printf("cd: no such file or directory: %s", newpath);
		all->exit_code = 1;
	}
	else
	{
		set_env_value(all, ft_strdup("OLDPATH"), ft_strdup(oldpath));
		set_env_value(all, ft_strdup("PWD"), ft_strdup(newpath));
		all->exit_code = 0;
	}
	free(newpath);
	free(oldpath);
	return ;
}