#include "./include/minishell.h"
// #include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	t_all	all;
	char	*str;

	(void)argc ;
	(void)argv ;
	init_env(&all, envp);
	// signal_handle();
	while (1)
	{
		// argv[0]으로 받아서 minishell 실행파일 이름 그 자체가 들어가도 될듯
		str = readline("minishell-0.0$ ");
		if (str)
		{
			add_history(str);
			parse_main(str, &all);

			/*********** test case (echo hi > test.txt 와 같은 경우) ***********/
			if (all.parser != NULL)
			{
				int fd;
				int stdin;
				int stdout;
				int stderr;
				int heredoc_count;
				std_save(&stdin, &stdout, &stderr);
				heredoc_count = heredoc_apply(all.parser);
				fd = red_apply(all.parser->left);
				if (all.parser->right != NULL)
					ms_echo(all.parser->right->content, &all);
				parse_free(all.parser);
				heredoc_tmp_file_delete(heredoc_count);
				free(str);
				std_restore(stdin, stdout, stderr);
				close(fd);
			}
			/************************** test end ****************************/

			// ms_echo(all.parser->right->content, &all);
			// parse_free(all.parser);
			// free(str);
		}
		else
			break ;
	}
	return (0);
}
