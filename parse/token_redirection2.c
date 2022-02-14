/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:50:00 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 00:53:46 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	str_split_free(char **str, int s_len)
{
	int		i;

	i = 0;
	while (i < s_len)
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
	return (1);
}

static int	token_ri_fdin(t_token **t_h, t_token **t, t_token **t_p, char **s)
{
	t_token		*token_new;

	if (s[0] != NULL)
	{
		token_new = token_malloc_init(s[0], fd_in);
		if (token_new == NULL)
			return (str_split_free(s, 3));
		if (*t_p == NULL)
			*t_h = token_head_insert(*t, token_new);
		else
			token_insert(*t_p, token_new);
		*t_p = token_new;
	}
	return (0);
}

static int	token_ri_fdout_num(t_token **token_new, char **str_split)
{
	int			i_check;
	char		*str_tmp;

	if (str_split[2][0] == '&')
	{
		str_tmp = ft_strdup_error_check(&str_split[2][1]);
		if (str_tmp == NULL)
			return (1);
		free(str_split[2]);
		str_split[2] = str_tmp;
		i_check = ft_is_fd_range(str_split[2], ft_strlen(str_split[2]));
		if (i_check == -2)
			*token_new = token_malloc_init(str_split[2], r_file);
		else if (0 <= i_check && i_check <= 10)
			*token_new = token_malloc_init(str_split[2], fd_out);
		else
		{
			str_tmp = ft_itoa(i_check);
			error_print3("minishell: ", str_tmp, ": Bad file descriptor", 1);
			if (str_tmp != NULL)
				free(str_tmp);
			return (1);
		}
	}	
	return (0);
}

int	token_redi_insert(t_token **t_h, t_token **t, t_token **t_p, char **s)
{
	t_token		*token_new;

	if (token_ri_fdin(t_h, t, t_p, s) == 1)
		return (1);
	free((*t)->str);
	(*t)->str = s[1];
	if (s[2] != NULL)
	{
		if (s[2][0] == '&')
		{
			if (token_ri_fdout_num(&token_new, s) == 1)
				return (1);
		}
		else
			token_new = token_malloc_init(s[2], r_file);
		if (token_new == NULL)
		{
			free(s[2]);
			return (1);
		}
		token_insert(*t, token_new);
		*t_p = *t;
		*t = token_new;
	}
	return (0);
}
