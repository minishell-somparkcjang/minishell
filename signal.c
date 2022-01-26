/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:12:11 by sompark           #+#    #+#             */
/*   Updated: 2022/01/25 17:39:37 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	parent_sigint(void)
{
	char	*buffer;

	buffer = ft_strdup(rl_line_buffer);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(2, buffer, ft_strlen(buffer));
	write(2, "  \b\b\nminishell-0.0$ ", 20);
	free(buffer);
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
			parent_sigint();
		else
			ft_putchar_fd('\n', 1);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(2, "  \b\b", 4);
		}
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	heredoc_sigint(int signo)
{	
	char	*buffer;

	(void)signo;
	buffer = ft_strdup(rl_line_buffer);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(2, buffer, ft_strlen(buffer));
	write(2, "  \b\b\n> ", 7);
	free(buffer);
}

void	signal_handle(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
