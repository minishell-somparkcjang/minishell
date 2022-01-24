/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:12:11 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 18:24:15 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\b\b  \b\b\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			ft_putchar_fd('\n', 1);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\b\b  \b\b", 1);
		}
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	signal_handle(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
