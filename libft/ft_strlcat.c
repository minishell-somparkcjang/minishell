/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:06:02 by sompark           #+#    #+#             */
/*   Updated: 2021/02/02 17:58:30 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_l;
	size_t	dst_l;
	size_t	ret;

	i = 0;
	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	if (dst_l >= dstsize)
		return (dstsize + src_l);
	ret = src_l + dst_l;
	while (src[i] && dst_l + 1 < dstsize)
	{
		dst[dst_l++] = src[i++];
	}
	dst[dst_l] = '\0';
	return (ret);
}
