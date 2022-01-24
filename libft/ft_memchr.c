/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 02:43:37 by sompark           #+#    #+#             */
/*   Updated: 2021/03/04 19:36:47 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp_s;
	unsigned char	find;
	size_t			i;

	i = 0;
	tmp_s = (unsigned char *)s;
	find = (unsigned char)c;
	while (i < n)
	{
		if (tmp_s[i] == find)
			return (tmp_s + i);
		i++;
	}
	return (NULL);
}
