/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:24:45 by cjang             #+#    #+#             */
/*   Updated: 2021/12/27 18:12:46 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_is_pos_int(char *s, int s_len, unsigned int start, unsigned int end)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while (i < s_len && num < end)
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + s[i] - '0';
		else
			return (0);
		i++;
	}
	if (i == s_len && start <= num && num <= end)
		return (1);
	else
		return (0);
}
