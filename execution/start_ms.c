#include "../include/minishell.h"

/*
WIFEXITED
자식 프로세스가 정상적으로 종료되었다면 TRUE
WIFSIGNALED
자식 프로세스가 시그널에 의해 종료되었다면 TRUE
WIFSTOPED
자식 프로세스가 중단되었다면 TRUE
WEXITSTATUS
자식 프로세스가 정상 종료되었을 때 반환한 값
WTERMSIG
자식 프로세스를 종료하도록한 신호의 번호 반환 (WIFSGNALED가 non
WSTOPSIG
자식을 정지하도록 야기한 신호의 숫자를 반환
*/

static int	exec_child(t_parse *parse, t_parse *parse_prev, t_all *all, pid_t pid)
{
	pipe_fd_connect(parse_prev, parse);
	if (red_apply(parse->left) == 1)
		return (pid);
	if (is_builtin(parse->right, all))
		exec_builtin(parse->right, all);
	else
		exec_cmd(parse->right, all, ret_env(all));
	exit(g_exit_code);
	return (0);
}

static pid_t	make_child(t_all *all, t_parse *parse, int heredoc_count)
{
	pid_t	pid;
	int		ret;
	t_parse	*parse_prev;
	int	i = 1;

	pipe(parse->pipe_fd);
	parse_prev = ret_parse_prev(all, parse);
	pid = fork();
	if (pid < 0)
		printf("Failed forking child..\n");
	else if (pid == 0)
	{
		ret = exec_child(parse, parse_prev, all, pid);
		if (ret != 0)
			return (ret);
	}
	pipe_fd_close(parse_prev, parse);
	return (pid);
}

static void	multi_cmd(t_all *all, int heredoc_count)
{
	pid_t	pid[2048];
	t_parse	*tmp_parse;
	int		i;
	int		status;

	i = 0;
	tmp_parse = all->parser;
	while (tmp_parse)
	{
		pid[i] = make_child(all, tmp_parse, heredoc_count);
		i++;
		tmp_parse = tmp_parse->next;
	}
	i = 0;
	while (i < all->pip_cnt)
	{
		waitpid(pid[i++], &status, 0);
		set_exit(status);
	}
}
static void	single_cmd(t_all *all, int heredoc_count)
{
	int fd;
	int stdin;
	int stdout;
	int stderr;

	std_save(&stdin, &stdout, &stderr);
	if (red_apply(all->parser->left) == 1)
	{
		std_restore(stdin, stdout, stderr);
		return ;
	}
	if (is_builtin(all->parser->right, all))
		exec_builtin(all->parser->right, all);
	else
		exec_single_cmd(all->parser->right, all, ret_env(all));
	std_restore(stdin, stdout, stderr);
}

void	start_ms(t_all *all)
{
	int heredoc_count;

	heredoc_count = heredoc_apply(all->parser);
	if (heredoc_count == -1)
		return ;
	if (all->pip_cnt == 1)
		single_cmd(all, heredoc_count);
	else
		multi_cmd(all, heredoc_count);
	heredoc_tmp_file_delete(heredoc_count);
}
