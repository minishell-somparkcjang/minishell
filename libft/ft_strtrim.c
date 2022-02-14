/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:55:00 by sompark           #+#    #+#             */
/*   Updated: 2021/03/04 21:03:39 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_start(char const *s, char const *set, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && ft_strchr(set, s[i]))
		i++;
	return (i);
}

static	size_t	ft_end(char const *s, char const *set, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && ft_strchr(set, s[len - i - 1]))
		i++;
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	s1_len;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	start = ft_start(s1, set, s1_len);
	end = ft_end(s1, set, s1_len);
	if (start >= end)
	{
		str = (char *)malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
