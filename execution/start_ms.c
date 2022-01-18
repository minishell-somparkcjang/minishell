#include "../include/minishell.h"

void	single_cmd(t_all *all)
{
	int stdin;
	int stdout;
	int stderr;
	int heredoc_count;

	//fd백업
	std_save(&stdin, &stdout, &stderr);
	heredoc_count = heredoc_apply(all->parser);
	red_apply(all->parser->left);
	if (is_builtin(all->parser->right, all))
		exec_builtin(all->parser->right, all);
	else
		exec_cmd(all->parser->right, all, ret_env(all));
	heredoc_tmp_file_delete(heredoc_count);
	std_restore(stdin, stdout, stderr);
	return ;
}

void	start_ms(t_all *all)
{
	//heredoc();
	if (all->parser->next == NULL)
		single_cmd(all);
	// else
	// 	multi_cmd(all);
	return ;
}
