#include "./include/minishell.h"

void	sigint_handler(int signo)
{
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	return ;
}

void	signal_handle(void)
{
	// ctrl + 'C'
	signal(SIGINT, sigint_handler);
	// ctrl + '\'
	signal(SIGQUIT, sigint_handler);
	// ctrl + 'D'
	signal(SIGTERM, sigint_handler);
}

// check = fork()
// if (check == 0)
// { all.flag = 1

// 	// 자식
// }
// else
// {
// 	flag = 0
// 	//부모
// }

// 파이프의 개념..? -> 시그널, 구조체
// A | B | C | D |
