/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:22 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 14:59:34 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* pwd */
static void	ms_pwd(void)
{
	char		*s;

	s = getcwd(NULL, 0);
	if (s != NULL)
		printf("%s\n", s);
	free(s);
	g_exit_code = 0;
}

/* env */
static void	ms_env(t_all *all)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_exit_code = 0;
}

void	exec_builtin(t_command *str, t_all *all)
{
	char	*command;
	char	**content;
	char	*lower_command;

	command = str->command;
	lower_command = ft_tolower(command);
	content = str->content;
	if (ft_strcmp(lower_command, "echo"))
		ms_echo(content);
	else if (ft_strcmp(command, "cd"))
		ms_cd(content, all);
	else if (ft_strcmp(lower_command, "pwd"))
		ms_pwd();
	else if (ft_strcmp(command, "export"))
		ms_export(content, all);
	else if (ft_strcmp(command, "unset"))
		ms_unset(content, all);
	else if (ft_strcmp(lower_command, "env"))
		ms_env(all);
	else if (ft_strcmp(command, "exit"))
		ms_exit(content);
	free(lower_command);
}

int	is_builtin(t_command *str)
{
	char	*command;
	char	*lower_command;

	command = str->command;
	lower_command = ft_tolower(command);
	if (ft_strcmp(lower_command, "echo")
		|| ft_strcmp(command, "cd")
		|| ft_strcmp(lower_command, "pwd") || ft_strcmp(command, "export")
		|| ft_strcmp(command, "unset") || ft_strcmp(lower_command, "env")
		|| ft_strcmp(command, "exit"))
	{
		free(lower_command);
		return (1);
	}
	free(lower_command);
	return (0);
}
