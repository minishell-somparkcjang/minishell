/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:15:50 by sompark           #+#    #+#             */
/*   Updated: 2020/12/24 15:16:58 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower(char *str)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(str);
	if (len == 0)
		return (NULL);
	ret = malloc(sizeof(char) * len + 1);
	while (str[i])
	{
		if (65 <= str[i] && str[i] <= 90)
			ret[i] = str[i] + 32;
		else
			ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
