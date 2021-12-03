/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:21:19 by cjang             #+#    #+#             */
/*   Updated: 2021/12/03 13:29:03 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell-0.0$ ");
		parse(str);
	}
	return (0);
}

//gcc main_tmp.c parse.c -o minishell -lreadline
