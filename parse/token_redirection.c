/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:01:11 by cjang             #+#    #+#             */
/*   Updated: 2022/01/23 16:05:58 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	token_rs_fdin(t_token *token, char **str_split, int *i, int *i_s)
{
	if (token->str[*i] >= '0' && token->str[*i] <= '9')
	{
		while (token->str[*i] != '<' && token->str[*i] != '>')
			*i += 1;
		str_split[0] = token_str_return(token->str, *i_s, *i);
		if (str_split[0] == NULL)
			return (1);
		*i_s = *i;
	}
	return (0);
}

static int	token_rs_fdout(t_token *token, char **str_split, int *i)
{
	int		i_start;

	i_start = *i;
	if (token->str[*i] != '\0')
	{
		while (token->str[*i] != '\0')
			*i += 1;
		str_split[2] = token_str_return(token->str, i_start, *i);
		if (str_split[2] == NULL)
		{
			if (str_split[0] != NULL)
				free(str_split[0]);
			free(str_split[1]);
			return (1);
		}
	}
	return (0);
}

static int	token_redi_split(t_token *token, char **str_split)
{
	int		i;
	int		i_start;

	i = 0;
	i_start = 0;
	if (token_rs_fdin(token, str_split, &i, &i_start) == 1)
		return (1);
	while (token->str[i] == '<' || token->str[i] == '>')
		i++;
	str_split[1] = token_str_return(token->str, i_start, i);
	if (str_split[1] == NULL)
	{
		if (str_split[0] != NULL)
			free(str_split[0]);
		return (1);
	}
	if (token_rs_fdout(token, str_split, &i) == 1)
		return (1);
	return (0);
}

static void	str_split_init(char **str, int s_len)
{
	int		i;

	i = 0;
	while (i < s_len)
	{
		str[i] = NULL;
		i++;
	}
}

int	token_redirection(t_token **t_head)
{
	t_token		*token_prev;
	t_token		*token;
	char		*str_split[3];

	token_prev = NULL;
	token = *t_head;
	while (token != NULL)
	{
		str_split_init(str_split, 3);
		if (token->type == r_in || token->type == r_out || \
			token->type == r_outapp || token->type == r_here)
		{
			if (token_redi_split(token, str_split) == 1)
				return (1);
			if (token_redi_insert(t_head, &token, &token_prev, str_split) == 1)
				return (1);
		}
		token_prev = token;
		token = token->next;
	}
	return (0);
}
