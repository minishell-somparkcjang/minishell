/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:03:10 by cjang             #+#    #+#             */
/*   Updated: 2022/01/24 23:46:15 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	token_str_change(t_token *token, char *s, int *index)
{
	char	*s_tmp;

	if (index[1] == 0)
		free(s);
	else
	{
		s_tmp = s;
		s = ft_strjoin(s, &token->str[index[1]]);
		free(s_tmp);
		if (s == NULL)
		{
			free(token->str);
			return (error_print_endl(strerror(errno), 1));
		}
		else if (ft_strlen(s) == 0 && token->type == r_file && index[2] == 0)
		{
			free(s);
			return (error_print3(\
			"minishell: ", token->str, ": ambiguous redirect", 1));
		}
		free(token->str);
		token->str = s;
	}
	return (0);
}

static char	*prev_special(t_token *token, char *s, int *index)
{
	char	*s_tmp;
	char	c;

	c = token->str[index[0]];
	token->str[index[0]] = '\0';
	s_tmp = s;
	s = ft_strjoin(s, &token->str[index[1]]);
	free(s_tmp);
	if (s == NULL)
		return (error_print_null(strerror(errno), 1));
	token->str[index[0]] = c;
	index[1] = index[0];
	return (s);
}

static char	*special_apply(t_all *all, t_token *token, char *s, int *index)
{
	char	*s_tmp;
	char	*s_next;

	s_next = NULL;
	if (token->str[index[0]] == '"' || token->str[index[0]] == '\'')
		index[2] = 1;
	if (token->str[index[0]] == '"')
		s_next = double_quote(&token->str[index[1]], &index[0], all);
	else if (token->str[index[0]] == '\'')
		s_next = single_quote(&token->str[index[1]], &index[0]);
	else if (token->str[index[0]] == '$')
		s_next = env_get(&token->str[index[1]], &index[0], all);
	if (s_next == NULL)
	{
		free(s);
		return (NULL);
	}
	s_tmp = s;
	s = ft_strjoin(s, s_next);
	free(s_tmp);
	free(s_next);
	if (s == NULL)
		return (error_print_null(strerror(errno), 1));
	return (s);
}

static int	token_special_func(t_all *all, t_token *token, char **s, int *index)
{
	if (token->str[index[0]] == '"' || token->str[index[0]] == '\'' \
	|| token->str[index[0]] == '$')
	{
		*s = prev_special(token, *s, index);
		if (*s == NULL)
			return (1);
		*s = special_apply(all, token, *s, index);
		if (*s == NULL)
			return (1);
		index[1] = index[0];
	}
	else
		index[0]++;
	return (0);
}

int	token_special(t_token *token, t_all *all)
{
	char	*s;
	int		index[3];

	while (token != NULL)
	{
		s = (char *)malloc(1 * sizeof(char));
		if (s == NULL)
			return (1);
		s[0] = '\0';
		index[0] = 0;
		index[1] = 0;
		index[2] = 0;
		while (token->str[index[0]] != '\0')
		{
			if (token_special_func(all, token, &s, index) == 1)
				return (1);
		}
		if (token_str_change(token, s, index) == 1)
			return (1);
		if (ft_strlen(token->str) == 0 && index[2] == 0)
			token->type = nontype;
		token = token->next;
	}
	return (0);
}
