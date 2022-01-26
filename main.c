/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:12:31 by sompark           #+#    #+#             */
/*   Updated: 2022/01/26 14:41:45 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	valid_str(char *str)
{
	if (!str)
	{
		ft_putendl_fd("exit", 2);
		exit(g_exit_code);
	}
	if (ft_isspace(str) || str[0] == '\0')
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;
	char	*str;

	(void)argc ;
	(void)argv ;
	init_env(&all, envp);
	signal_handle();
	while (1)
	{
		signal_handle();
		str = readline("minishell-0.0$ ");
		if (valid_str(str))
		{
			add_history(str);
			parse_main(str, &all);
			start_ms(&all);
			parse_free(all.parser);
		}
		else
			g_exit_code = 258;
		free(str);
	}
	return (0);
}
