/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:12:15 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:12:18 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/* 문자열비교 */
int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if ((str1 == NULL && str2 != NULL) || (str2 == NULL && str1 != NULL))
		return (0);
	if (str1 == NULL && str2 == NULL)
		return (1);
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0' || str2[i] == '\0')
			break ;
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

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

t_parse	*ret_parse_prev(t_all *all, t_parse *parse)
{
	t_parse	*tmp;

	tmp = all->parser;
	if (tmp == parse)
		return (NULL);
	while (tmp)
	{
		if (tmp->next == parse)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_isspace(char *str)
{
	int	i;
	int	nb;

	i = -1;
	nb = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r'
			|| str[i] == ' ')
			nb++;
	}
	if (nb == ft_strlen(str))
		return (1);
	return (0);
}
