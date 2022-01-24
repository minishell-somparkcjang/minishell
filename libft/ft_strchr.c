/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:03:24 by sompark           #+#    #+#             */
/*   Updated: 2021/03/04 20:53:09 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int character)
{
	unsigned char	find;

	find = character;
	while (*str)
	{
		if (*str == find)
			return ((char *)str);
		str++;
	}
	if (*str == find)
		return ((char *)str);
	return (0);
}
