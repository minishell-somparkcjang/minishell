/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:41:21 by cjang             #+#    #+#             */
/*   Updated: 2022/01/25 13:41:46 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_print_endl(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	g_exit_code = exit_code;
	return (1);
}

void	*error_print_null(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	g_exit_code = exit_code;
	return (NULL);
}
