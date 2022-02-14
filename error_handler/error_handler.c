/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:30:46 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:08:34 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	g_exit_code = exit_code;
	exit(exit_code);
}

int	error_print(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	g_exit_code = exit_code;
	return (1);
}

int	error_print3(char *str1, char *str2, char *str3, int exit_code)
{
	if (str1 != NULL)
		ft_putstr_fd(str1, 2);
	if (str2 != NULL)
		ft_putstr_fd(str2, 2);
	if (str3 != NULL)
		ft_putendl_fd(str3, 2);
	else
		ft_putchar_fd('\n', 2);
	g_exit_code = exit_code;
	return (1);
}

void	error_handler(char *arg, int _errno)
{
	struct stat	dir_stat;

	if (stat(arg, &dir_stat) == 0 && S_ISDIR(dir_stat.st_mode))
	{
		error_print("minishell: ", 126);
		error_print(arg, 126);
		error_exit(": is a directory\n", 126);
	}
	if (_errno == 13)
		error_exit(strerror(errno), 126);
	else if (_errno == 8)
		error_exit(strerror(errno), 1);
	else
	{
		error_print("minishell: ", 127);
		error_print(arg, 127);
		error_exit(": command not found\n", 127);
	}
}
