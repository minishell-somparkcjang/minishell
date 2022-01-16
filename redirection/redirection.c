/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:30:39 by cjang             #+#    #+#             */
/*   Updated: 2022/01/16 16:42:15 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

int	heredoc_apply(t_redirection *red_head)
{
	t_redirection	*red;
	int				fd;

	red = red_head;
	while (red != NULL)
	{
		// heredoc의 작동원리를 찾아봐야할 듯.
	}
}

int	red_apply(t_redirection *red_head)
{
	t_redirection	*red;
	int				fd;
	int				i_check;

	red = red_head;
	while (red != NULL)
	{
		// 각각의 리다이렉션 타입에 맞게 파일 오픈
		if (red->file_name != NULL && red->type == r_in)
			fd = open(red->file_name, O_RDONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (red->file_name != NULL && red->type == r_out)
			fd = open(red->file_name, O_RDWR | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (red->file_name != NULL && red->type == r_outapp)
			fd = open(red->file_name, O_RDWR | O_CREAT | O_APPEND, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (red->type == r_here)
			fd = 1;
		else
			fd = red->fd_right;
		// 실패시 예외처리, return (-1)
		if (fd < 0)
		{
			printf("open_fail\n");
			exit(1);
		}
		// dup2를 이용하여 fd 수정
		if (red->type == r_in)
			i_check = dup2(fd, red->fd_left);
		else if (red->type == r_out | red->type == r_outapp)
			i_check = dup2(fd, red->fd_left);
		else
			i_check = 1;
		// 실패시 예외처리, return (-1)
		if (i_check == -1)
		{
			printf("dup2 fail\n");
			exit(1);
		}
		close(fd);
		red = red->next;
	}
	return (fd);
}
/* close()의 타이밍은? */

// /* 대략 이런느낌 */
// void	red_test(t_redirection *red_head)
// {
// 	pid_t	pid;

// 	// while (parse != NULL)
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		red_apply(red_head);
// 		// command 실행
// 		exit(0);
// 	}
// 	// parse = parse->next;
// }
