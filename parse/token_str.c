/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:57:37 by cjang             #+#    #+#             */
/*   Updated: 2022/01/18 01:53:36 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* token_str용 함수 */
static char	*token_str_return(char *s, int i_start, int i_end)
{
	char	c;
	char	*str;

	c = s[i_end];
	s[i_end] = '\0';
	str = ft_strdup(&s[i_start]);
	s[i_end] = c;
	return (str);
}

static int	redirection_check(char *s, int *i, int *r_flag, int i_tmp)
{
	int		i_check;

	i_check = ft_is_fd_range(&s[i_tmp], *i - i_tmp);
	if (*i != i_tmp && i_check == -2)
		return (2);
	// 에러처리 (보완필요)
	else if (*i != i_tmp && 256 <= i_check && i_check <= 0x7FFFFFFF)
	{
		printf("bash: %d: Bad file descriptor\n", i_check);
		return (1);
	}
	else if (*i != i_tmp && i_check == -1)
	{
		ft_putendl_fd("bash: file descriptor out of range: Bad file descriptor", 2);
		return (1);
	}
	else
	{
		if (s[*i] == s[*i + 1])
			*i += 1;
		*r_flag = 1;
		return (0);
	}	
}

static char	*next_str(char *s, int *i, int i_tmp)
{
	char	*str;

	if (s[*i] == ' ')
	{
		s[*i] = '\0';
		str = ft_strdup(&s[i_tmp]);
		s[*i] = ' ';
		*i += 1;
		while (s[*i] == ' ')
			*i += 1;
		return (str);
	}
	else if (s[*i] == '|' && i_tmp == *i)
	{
		*i += 1;
		while (s[*i] == ' ')
			*i += 1;
		return (ft_strdup("|"));
	}
	else if (s[*i] == '|' && i_tmp != *i)
		return (token_str_return(s, i_tmp, *i));
	else
		return (ft_strdup(&s[i_tmp]));
}

char	*token_str(char *s, int *i)
{
	int		i_tmp;
	int		quo_flag;
	int		r_flag;
	int		i_check;

	quo_flag = 0;
	r_flag = 0;
	i_tmp = *i;
	while (((s[*i] != '|' && s[*i] != ' ') || quo_flag != 0) && s[*i] != '\0')
	{
		if (s[*i] == '\'' && quo_flag == 0)
			quo_flag = 1;
		else if (s[*i] == '\"' && quo_flag == 0)
			quo_flag = 2;
		else if (s[*i] == '\'' && quo_flag == 1)
			quo_flag = 0;
		else if (s[*i] == '\"' && quo_flag == 2)
			quo_flag = 0;
		else if ((s[*i] == '<' || s[*i] == '>') && r_flag == 0 && quo_flag == 0)
		{
			i_check = redirection_check(s, i, &r_flag, i_tmp);
			if (i_check == 1)
				return (NULL);
			else if (i_check == 2)
				return (token_str_return(s, i_tmp, *i));
		}
		else if ((s[*i] == '<' || s[*i] == '>') && r_flag == 1)
			return (token_str_return(s, i_tmp, *i));
		*i += 1;
	}
	return (next_str(s, i, i_tmp));
}
