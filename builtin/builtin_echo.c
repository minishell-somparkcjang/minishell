/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:09 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:12:25 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_option(char *content)
{
	int	i;

	i = 0;
	if (content[i++] == '-')
	{
		while (content[i])
		{
			if (content[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	ms_echo(char **content)
{
	int	i;
	int	nlflag;

	if (content[1] == NULL)
	{
		printf("\n");
		g_exit_code = 0;
		return ;
	}
	nlflag = 0;
	i = 1;
	if (is_option(content[1]))
	{
		nlflag = 1;
		i = 2;
	}
	while (content[i])
	{
		printf("%s", content[i++]);
		if (content[i])
			printf(" ");
	}
	if (!nlflag)
		printf("\n");
	g_exit_code = 0;
}
