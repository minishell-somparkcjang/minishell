/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_backup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:33:14 by cjang             #+#    #+#             */
/*   Updated: 2022/01/13 17:41:21 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	std_save(int *stdin, int *stdout, int *stderr)
{
	*stdin = dup(0);
	*stdout = dup(1);
	*stderr = dup(2);
}

void	std_restore(int stdin, int stdout, int stderr)
{
	dup2(stdin, 0);
	dup2(stdout, 1);
	dup2(stderr, 2);
}
