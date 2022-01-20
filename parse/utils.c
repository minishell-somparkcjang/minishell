/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:01:47 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 16:19:18 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup_error_check(char *str)
{
	char	*s_return;

	s_return = ft_strdup(str);
	if (s_return == NULL)
		error_print(strerror(errno), 1);
	return (s_return);
}

int	quotes_flag_check(char c, int quotes_flag)
{
	if (c == '\'' && quotes_flag == 0)
		quotes_flag = 1;
	else if (c == '\"' && quotes_flag == 0)
		quotes_flag = 2;
	else if (c == '\'' && quotes_flag == 1)
		quotes_flag = 0;
	else if (c == '\"' && quotes_flag == 2)
		quotes_flag = 0;
	return (quotes_flag);
}

void	*error_print_null(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	g_exit_code = exit_code;
	return (NULL);
}
