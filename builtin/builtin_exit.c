/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:12 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:12:25 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_valid(int valid, char *content)
{
	if (valid)
	{
		ft_putendl_fd("exit\n", 1);
		exit(ft_atoi(content));
	}
	else
	{
		error_print("exit\nminishell: exit ", 255);
		error_print(content, 255);
		error_exit(": numeric argument required\n", 255);
	}
}

void	ms_exit(char **content)
{
	int	valid;
	int	i;

	valid = 1;
	i = 0;
	if (content[1] == NULL)
	{
		ft_putendl_fd("exit\n", 1);
		exit(0);
	}
	if (content[2] == NULL)
	{
		while (content[1][i])
		{
			if (!ft_isdigit(content[1][i]))
			{
				valid = 0;
				break ;
			}
			i++;
		}
		exit_valid(valid, content[1]);
	}
	else
		error_print("exit\nminishell: exit: too many arguments\n", 1);
}
