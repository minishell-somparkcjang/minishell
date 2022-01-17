/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:00:54 by cjang             #+#    #+#             */
/*   Updated: 2022/01/17 16:14:30 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** 파이프 생성은 자식 프로세스를 생성하기 전에 부모 프로세스에서 생성해야함.
** 그렇지 않으면 파이프로 인해 생성된 파일스크립트를 닫을 수가 없음
*/

int	pipe_init(t_parse *parse_prev, t_parse *parse)
{
	if (parse_prev == NULL)
	{
		dup2(parse->pipe_fd[1], 1);
		close(parse->pipe_fd[0]);
	}
	// 마지막 명령은 파이프가 없다고 가정
	else if (parse-> next == NULL)
	{
		dup2(parse_prev->pipe_fd[0], 0);
	}
	else
	{
		dup2(parse_prev->pipe_fd[0], 0);
		dup2(parse->pipe_fd[1], 1);
		close(parse->pipe_fd[0]);
	}
	return (1);
}
