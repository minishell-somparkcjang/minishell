/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:26:48 by sompark           #+#    #+#             */
/*   Updated: 2021/02/22 01:31:22 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t size)
{
	size_t			i;
	unsigned char	tmp_val;
	unsigned char	*str;

	tmp_val = (unsigned char)value;
	str = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		str[i] = tmp_val;
		i++;
	}
	return (ptr);
}
