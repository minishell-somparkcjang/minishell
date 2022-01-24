/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:11:25 by sompark           #+#    #+#             */
/*   Updated: 2021/01/20 17:05:16 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int character)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	while (tmp != str)
	{
		if (*tmp == character)
			return (tmp);
		tmp--;
	}
	if (*tmp == character)
		return (tmp);
	return (0);
}
