/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:24:45 by cjang             #+#    #+#             */
/*   Updated: 2022/01/07 15:45:47 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 문자열이 int형 양수값 안에 들어가는지 체크 */
int	ft_is_fd_range(char *s, int s_len)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while (i < s_len && num <= 0x7FFFFFFF)
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + s[i] - '0';
		else
			return (-2);
		i++;
	}
	if (i == s_len && 0 <= num && num <= 0x7FFFFFFF)
		return (num);
	while (i < s_len)
		if (s[i] >= '0' && s[i] <= '9')
			i++;
	if (i < s_len)
		return (-2);
	else
		return (-1);
}

/* 문자열 두개 중 가장 긴 값의 문자열 길이를 반환 */
size_t	ft_strlen_long(const char *s1, const char *s2)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (s1[i1] != '\0')
		i1++;
	while (s2[i2] != '\0')
		i2++;
	if (i1 > i2)
		return (i1);
	else
		return (i2);
}
