/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:01:47 by cjang             #+#    #+#             */
/*   Updated: 2022/01/25 13:41:31 by cjang            ###   ########.fr       */
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
