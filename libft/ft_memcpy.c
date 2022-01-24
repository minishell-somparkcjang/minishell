/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:52:56 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:10:25 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	unsigned char	*dst;
	unsigned char	*src;

	if (!dest && !source)
		return (0);
	dst = (unsigned char *)dest;
	src = (unsigned char *)source;
	while (num--)
	{
		*dst++ = *src++;
	}
	return (dest);
}
