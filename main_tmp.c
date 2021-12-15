/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:21:19 by cjang             #+#    #+#             */
/*   Updated: 2021/12/15 17:28:17 by cjang            ###   ########.fr       */
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
	int i = 0;
	while (1)
	{
		str = readline("minishell-0.0$ ");
		parse(str, &all);
	}
	return (0);
}

//gcc main_tmp.c parse.c -o minishell -lreadline
