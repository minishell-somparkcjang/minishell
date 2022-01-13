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
			parse_main(str, &all);
			//test
			// ms_echo(all.parser->right->content);
			add_history(str);
			parse_free(all.parser);
			free(str);
		}
		else
			break ;
	}
	return (0);
}