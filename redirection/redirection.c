/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:30:39 by cjang             #+#    #+#             */
/*   Updated: 2022/01/25 17:14:56 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	red_open(t_redirection *red)
{
	int		fd;

	if (red->file_name != NULL && \
	(red->type == r_in || red->type == r_here))
		fd = open(red->file_name, O_RDONLY, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (red->file_name != NULL && red->type == r_out)
		fd = open(red->file_name, O_RDWR | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (red->file_name != NULL && red->type == r_outapp)
		fd = open(red->file_name, O_RDWR | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = red->fd_right;
	return (fd);
}

int	red_apply(t_redirection *red_head)
{
	t_redirection	*red;
	int				fd;
	int				i_check;

	red = red_head;
	while (red != NULL)
	{
		fd = red_open(red);
		if (fd < 0)
			return (error_print_endl(strerror(errno), 1));
		if (red->type == r_in || red->type == r_here || \
		red->type == r_out || red->type == r_outapp)
			i_check = dup2(fd, red->fd_left);
		else
			i_check = 1;
		if (i_check == -1)
			return (error_print_endl(strerror(errno), 1));
		close(fd);
		red = red->next;
	}
	return (0);
}
