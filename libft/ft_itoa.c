/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:27:45 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:07:52 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_getdigit(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		num;
	char	*ret;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num = ft_getdigit(n);
	ret = (char *)malloc(sizeof(char) * (num + 1));
	ret[num--] = '\0';
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	if (n < 0)
	{
		ret[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		ret[num--] = (n % 10) + '0';
		n = n / 10;
	}
	return (ret);
}
