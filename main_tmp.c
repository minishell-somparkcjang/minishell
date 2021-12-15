/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:21:19 by cjang             #+#    #+#             */
/*   Updated: 2021/12/15 19:49:52 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_all	all;
	char	*str;

	(void)argc ;
	(void)argv ;
	(void)envp ;
	init_env(&all, envp);
	while (1)
	{
		str = readline("minishell-0.0$ ");
		if (str)
		{
			parse(str, &all);
			add_history(str);
			free(str);
		}
		else
			break ;
	}
	return (0);
}

// gcc main_tmp.c parse.c -o minishell -lreadline
// 터미널 실행중 시그널을 받으면 어떻게 처리해야하는거지..?
