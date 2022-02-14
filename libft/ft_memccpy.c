/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:36:59 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:10:42 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)src == (unsigned char)c)
		{
			*(unsigned char *)dst++ = *(unsigned char *)src;
			return (dst);
		}
		*(unsigned char *)dst++ = *(unsigned char *)src++;
		n--;
	}
	return (NULL);
}
