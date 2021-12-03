/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:12 by cjang             #+#    #+#             */
/*   Updated: 2021/12/03 13:48:07 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *str)
{
	char	**split_str;
	int		i;

	split_str = ft_split(str, ' ');
	i = 0;
	while (split_str[i])
	{
		printf("%s\n", split_str[i]);
		i++;
	}
	free(split_str);
}
	// argv로 들어오는게 아니라서 띄어쓰기, '' "" 각각에 대해 대응을 해야 함.
	// 일단 split으로 나눠보기
