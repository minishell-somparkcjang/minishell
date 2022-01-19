/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:30:46 by sompark           #+#    #+#             */
/*   Updated: 2022/01/19 18:02:20 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	g_exit_code = exit_code;
	exit(exit_code);
}

int	error_print(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
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
