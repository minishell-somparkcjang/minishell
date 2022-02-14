/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:51:24 by cjang             #+#    #+#             */
/*   Updated: 2022/01/19 17:54:19 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_type	type_check(char *s, t_token *token_prev)
{
	t_type		t;
	char		*str;

	if (s[0] == '|')
		t = pip;
	else if (s[0] == '<' && s[1] == '<')
		t = r_here;
	else if (s[0] == '>' && s[1] == '>')
		t = r_outapp;
	else if (s[0] == '<')
		t = r_in;
	else if (s[0] == '>')
		t = r_out;
	else if (token_prev != NULL && ft_strlen(token_prev->str) > 0)
	{
		str = token_prev->str;
		if (str[ft_strlen(str) - 1] == '<' || str[ft_strlen(str) - 1] == '>')
			t = r_file;
		else
			t = com;
	}
	else
		t = com;
	return (t);
}

t_type	token_type(t_token *token_prev, t_token *token)
{
	int		i;
	int		quotes_flag;
	char	*s;

	i = 0;
	quotes_flag = 0;
	s = token->str;
	while (((s[i] != '|' && s[i] != '<' && s[i] != '>') || quotes_flag != 0) \
	&& s[i] != '\0')
	{
		quotes_flag = quotes_flag_check(s[i], quotes_flag);
		i++;
	}
	return (type_check(&s[i], token_prev));
}
