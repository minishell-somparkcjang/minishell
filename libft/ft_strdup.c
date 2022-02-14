/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:44:41 by sompark           #+#    #+#             */
/*   Updated: 2021/03/03 11:39:08 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*tmp;
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	tmp = malloc(src_len + 1);
	if (!tmp)
		return (0);
	while (src[i])
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
