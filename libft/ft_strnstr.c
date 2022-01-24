/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:17:05 by sompark           #+#    #+#             */
/*   Updated: 2021/03/04 20:51:20 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	pos;

	if (!*little)
		return ((char *)big);
	if (n == 0)
		return (NULL);
	pos = 0;
	while (big[pos] && pos < n)
	{
		i = 0;
		j = pos;
		while (little[i] && big[j] == little[i] && j < n)
		{
			i++;
			j++;
		}
		if (little[i] == '\0')
			return ((char *)(big + pos));
		pos++;
	}
	return (NULL);
}
