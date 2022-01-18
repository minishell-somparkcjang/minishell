/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:30:39 by cjang             #+#    #+#             */
/*   Updated: 2022/01/18 16:34:11 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc_tmp_file_delete(int tmp_count)
{
	char	*filename;
	char	*str;
	int		i;
	int		i_check;

	i = 0;
	while (i <= tmp_count)
	{
		str = ft_itoa(i);
		if (str == NULL)
			return (1);
		filename = ft_strjoin("tmp__heredoc__", str);
		if (filename == NULL)
			return (1);
		free(str);
		i_check = unlink(filename);
		if (i_check != 0)
		{
			free(filename);
			return (i_check);
		}
		free(filename);
		i++;
	}
	return (0);
}

/*
** 리턴 값에 대해서도 정의를 내려야 할 듯
**	0	정상종료
**	1	해당 함수 실행 조건 부적합, 동적할당 실패
**	-1	내부 함수 실행 실패
*/
static int	heredoc_tmp_file_create(t_redirection *red, int index)
{
	int		fd;
	char	*filename;
	char	*str;

	if (red->type != r_here || red->file_name == NULL)
		return (1);
	str = ft_itoa(index);
	if (str == NULL)
		return (1);
	filename = ft_strjoin("tmp__heredoc__", str);
	free(str);
	if (filename == NULL)
		return (1);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_putendl_fd("open fail", 2);
		return (fd);
	}
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		else if (ft_strncmp(str, red->file_name, \
		ft_strlen_long(str, red->file_name)) == 0)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, fd);
		free(str);
	}
	free(red->file_name);
	red->file_name = filename;
	close(fd);
	return (0);
}

int	heredoc_apply(t_parse *parse_head)
{
	t_parse			*parse;
	t_redirection	*red;
	int				i;
	int				here_flag;

	i = -1;
	parse = parse_head;
	while (parse != NULL)
	{
		red = parse->left;
		here_flag = 0;
		while (red != NULL)
		{
			if (red->type == r_here)
			{
				if (here_flag == 0)
					i++;
				heredoc_tmp_file_create(red, i);
				here_flag = 1;
			}
			red = red->next;
		}
		parse = parse->next;
	}
	return (i);
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
		// 실패시 예외처리, return (-1)
		if (fd < 0)
		{
			ft_putendl_fd("open fail", 2);
			return (1);
		}
		// dup2를 이용하여 fd 수정
		if (red->type == r_in || red->type == r_here || \
		red->type == r_out || red->type == r_outapp)
			i_check = dup2(fd, red->fd_left);
		else
			i_check = 1;
		// 실패시 예외처리, return (-1)
		if (i_check == -1)
		{
			ft_putendl_fd("dup2 fail", 2);
			return (1);
		}
		close(fd);
		red = red->next;
	}
	return (0);
}
