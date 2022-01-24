/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 00:54:01 by sompark           #+#    #+#             */
/*   Updated: 2021/03/03 11:41:35 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	s_len;

	if (!s)
		return (0);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		ret[0] = 0;
		return (ret);
	}
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
