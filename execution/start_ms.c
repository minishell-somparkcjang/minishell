/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:55:17 by sompark           #+#    #+#             */
/*   Updated: 2022/01/25 17:42:25 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_child(t_parse *parse, t_all *all, pid_t pid, char **envp)
{
	t_parse	*parse_prev;

	parse_prev = ret_parse_prev(all, parse);
	pipe_fd_connect(parse_prev, parse);
	if (red_apply(parse->left) == 1)
		return (pid);
	if (parse->right != NULL)
	{
		if (is_builtin(parse->right))
			exec_builtin(parse->right, all);
		else
			exec_cmd(parse->right, all, envp);
	}
	exit(g_exit_code);
	return (0);
}

static pid_t	make_child(t_all *all, t_parse *parse, char **envp)
{
	pid_t	pid;
	int		ret;
	t_parse	*parse_prev;

	if (parse->next != NULL)
		pipe(parse->pipe_fd);
	parse_prev = ret_parse_prev(all, parse);
	pid = fork();
	if (pid < 0)
		printf("Failed forking child..\n");
	else if (pid == 0)
	{
		ret = exec_child(parse, all, pid, envp);
		if (ret != 0)
			return (ret);
	}
	pipe_fd_close(parse_prev, parse);
	return (pid);
}

static void	multi_cmd(t_all *all)
{
	pid_t	pid[2048];
	t_parse	*tmp_parse;
	int		i;
	int		status;
	char	**envp;

	i = 0;
	envp = ret_env(all);
	tmp_parse = all->parser;
	while (tmp_parse)
	{
		pid[i++] = make_child(all, tmp_parse, envp);
		tmp_parse = tmp_parse->next;
	}
	i = 0;
	while (i < all->pip_cnt)
	{
		waitpid(pid[i++], &status, 0);
		set_exit(status);
	}
	free_env(envp);
}

static void	single_cmd(t_all *all)
{
	int		stdin;
	int		stdout;
	int		stderr;
	char	**envp;

	std_save(&stdin, &stdout, &stderr);
	envp = ret_env(all);
	if (red_apply(all->parser->left) == 1)
		return ;
	if (all->parser->right != NULL)
	{
		if (is_builtin(all->parser->right))
			exec_builtin(all->parser->right, all);
		else
			exec_single_cmd(all->parser->right, all, envp);
	}
	std_restore(stdin, stdout, stderr);
	free_env(envp);
}

void	start_ms(t_all *all)
{
	int	heredoc_count;

	heredoc_count = heredoc_apply(all->parser);
	if (heredoc_count < 0)
		return ;
	if (all->parser == NULL)
		return ;
	if (all->pip_cnt == 1)
		single_cmd(all);
	else
		multi_cmd(all);
	heredoc_tmp_file_delete(heredoc_count);
}
