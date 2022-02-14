/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 02:28:43 by sompark           #+#    #+#             */
/*   Updated: 2021/02/23 02:31:36 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t num)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	dst = (unsigned char *)dest;
	src = (unsigned char *)source;
	i = 0;
	if (src < dst)
	{
		while (i < num)
		{
			dst[num - 1 - i] = src[num - 1 - i];
			i++;
		}
		return (dest);
	}
	else if (src > dst)
	{
		while (i < num)
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (dest);
}
