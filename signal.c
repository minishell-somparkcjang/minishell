#include "./include/minishell.h"

void	sigint_handler(int signo)
{

}

void	signal_handle(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, );
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