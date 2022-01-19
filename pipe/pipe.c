/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:00:54 by cjang             #+#    #+#             */
/*   Updated: 2022/01/19 16:30:47 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_fd_connect(t_parse *parse_prev, t_parse *parse)
{
	if (parse_prev == NULL)
	{
		dup2(parse->pipe_fd[1], 1);
		close(parse->pipe_fd[0]);
		close(parse->pipe_fd[1]);
	}
	else if (parse-> next == NULL)
	{
		dup2(parse_prev->pipe_fd[0], 0);
		close(parse_prev->pipe_fd[0]);
	}
	else
	{
		dup2(parse_prev->pipe_fd[0], 0);
		dup2(parse->pipe_fd[1], 1);
		close(parse_prev->pipe_fd[0]);
		close(parse->pipe_fd[0]);
		close(parse->pipe_fd[1]);
	}
	return (1);
}

int	pipe_fd_close(t_parse *parse_prev, t_parse *parse)
{
	if (parse_prev == NULL)
		close(parse->pipe_fd[1]);
	else if (parse-> next == NULL)
		close(parse_prev->pipe_fd[0]);
	else
	{
		close(parse_prev->pipe_fd[0]);
		close(parse->pipe_fd[1]);
	}
	return (1);
}
