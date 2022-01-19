/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:10:17 by cjang             #+#    #+#             */
/*   Updated: 2022/01/19 18:05:59 by cjang            ###   ########.fr       */
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
	while (i < tmp_count)
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

static void	heredoc_command(t_redirection *red, int fd)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			return ;
		else if (ft_strncmp(str, red->file_name, \
		ft_strlen_long(str, red->file_name)) == 0)
		{
			free(str);
			return ;
		}
		ft_putendl_fd(str, fd);
		free(str);
	}
}

static int	heredoc_tmp_file_create(t_redirection *red, int index)
{
	int		fd;
	char	*filename;
	char	*str;

	if (red->type != r_here || red->file_name == NULL)
		return (1);
	str = ft_itoa(index);
	if (str == NULL)
		return (error_print(strerror(errno), 1));
	filename = ft_strjoin("tmp__heredoc__", str);
	free(str);
	if (filename == NULL)
		return (error_print(strerror(errno), 1));
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (error_print(strerror(errno), 1));
	heredoc_command(red, fd);
	free(red->file_name);
	red->file_name = filename;
	close(fd);
	return (0);
}

static int	heredoc_func(t_redirection *red, int *i, int *here_flag)
{
	if (*here_flag == 0)
		*i += 1;
	if (heredoc_tmp_file_create(red, *i) == 1)
	{
		heredoc_tmp_file_delete(*i - 1);
		return (1);
	}
	*here_flag = 1;
	return (0);
}

/*
** -1	비정상 종료
*/
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
				if (heredoc_func(red, &i, &here_flag) == 1)
					return (-1);
			}
			red = red->next;
		}
		parse = parse->next;
	}
	return (i + 1);
}
