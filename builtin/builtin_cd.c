#include "../include/minishell.h"

static char *set_home_dir(t_all *all, char *path)
{
	int	len;
	char *home;

	len = ft_strlen(path);
	if (len == 1)
		return (ft_strdup(find_env_key(all, "HOME")));
	else
	{
		home = find_env_key(all, "HOME");
		return (ft_strjoin(home, &path[1]));
	}
}

static char	*find_newpath(char *path, t_all *all)
{
	if (*path == '~')
		return (set_home_dir(all, path));
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
		g_exit_code = 1;
		return ;
	}
	if (chdir(newpath) == -1)
	{
		error_print("cd: no such file or directory: ", 1);
		error_print(newpath, 1);
		error_print("\n", 1);
	}
	else
	{
		set_env_value(all, ft_strdup("OLDPATH"), ft_strdup(oldpath));
		set_env_value(all, ft_strdup("PWD"), ft_strdup(newpath));
		g_exit_code = 0;
	}
	free(newpath);
	free(oldpath);
	return ;
}