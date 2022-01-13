#include "../include/minishell.h"
#include <fcntl.h>

void	red_apply(t_redirection *red_head)
{
	t_redirection	*red;
	int			fd;
	int			i_check;

	red = red_head;
	while (red != NULL)
	{
		// 각각의 리다이렉션 타입에 맞게 파일 오픈
		if (red->file_name != NULL && red->type == r_in)
		{
			// fd = open(red->file_name, )
			// 실패시 예외처리
		}
		else if (red->file_name != NULL && red->type == r_out)
		{
			fd = open(red->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			// 실패시 예외처리
		}
		else if (red->file_name != NULL && red->type == r_outapp)
		{
			// fd = open(red->file_name, )
			// 실패시 예외처리
		}
		else if (red->file_name != NULL && red->type == r_here)
		{
			// fd = open(red->file_name, )
			// 실패시 예외처리
		}
		else
		{
			fd = red->fd_right;
		}
		// dup2를 이용하여 fd 수정
		if (red->type == r_in || red->type == r_here)
		{
			// dup2(fd, fd_left)
		}
		else
		{
			i_check = dup2(fd, red->fd_left);
			// 실패시 예외처리
		}
		red = red->next;
	}
}
// close()의 타이밍은?

/* 대략 이런느낌 */
void	red_test(t_redirection *red_head)
{
	pid_t	pid;
	
	// while (parse != NULL)
	pid = fork();
	if (pid == 0)
	{
		red_apply(red_head);
		// command 실행
		exit(0);
	}
	// parse = parse->next;
}