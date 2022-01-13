#include "./include/minishell.h"
// #include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	t_all	all;
	char	*str;
	int		fd;
	int		stdin;
	int		stdout;
	int		stderr;

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
			//test
			std_save(&stdin, &stdout, &stderr);
			fd = red_apply(all.parser->left);
			ms_echo(all.parser->right->content, &all);

			parse_free(all.parser);
			free(str);
			std_restore(stdin, stdout, stderr);
			close(fd);
		}
		else
			break ;
	}
	return (0);
}
