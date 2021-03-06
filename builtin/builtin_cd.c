/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:02 by sompark           #+#    #+#             */
/*   Updated: 2022/01/25 17:04:54 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*set_home_dir(t_all *all, char *path)
{
	int		len;
	char	*home;
	char	*tmp;

	len = ft_strlen(path);
	if (len == 1)
	{
		tmp = find_env_key(all, "HOME");
		if (!tmp)
			return (NULL);
		return (ft_strdup(tmp));
	}
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

static void	change_dir(char *newpath, char *oldpath, t_all *all)
{
	if (chdir(newpath) == -1)
	{
		error_print("cd: no such file or directory: ", 1);
		error_print(newpath, 1);
		error_print("\n", 1);
	}
	else
	{
		set_env_value(all, ft_strdup("OLDPWD"), ft_strdup(oldpath));
		set_env_value(all, ft_strdup("PWD"), ft_strdup(newpath));
		g_exit_code = 0;
	}
}

static char	*single_cd(t_all *all)
{
	char	*tmp;

	tmp = find_env_key(all, "HOME");
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp));
}

void	ms_cd(char **content, t_all *all)
{
	char	*oldpath;
	char	*newpath;

	if (content[1] == NULL)
		newpath = single_cd(all);
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
	change_dir(newpath, oldpath, all);
	free(newpath);
	free(oldpath);
	return ;
}
