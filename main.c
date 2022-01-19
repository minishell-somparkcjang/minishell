#include "./include/minishell.h"
// #include <readline/history.h>

int	valid_str(char *str)
{
	if (!str)
	{
		ft_putendl_fd("MINISHELL$ exit\n", 2);
		exit(g_exit_code);
	}
	if (ft_isspace(str) || str[0] == '\0')
		return (0);
	return (1);
}

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
		if (valid_str(str))
		{
			add_history(str);
			parse_main(str, &all);
			start_ms(&all);
			parse_free(all.parser);
			free(str);
		}
		else
			g_exit_code = 258;
	}
	return (0);
}

