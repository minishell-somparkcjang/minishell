/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:02:15 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 15:49:20 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	token_type_func(t_token *token_head)
{
	t_token		*token;
	t_token		*token_prev;

	token = token_head;
	token_prev = NULL;
	while (token != NULL)
	{
		token->type = token_type(token_prev, token);
		token_prev = token;
		token = token->next;
	}
}

static int	token_struct_func(t_token **token_head, t_token **token)
{
	t_token		*token_prev;

	if (*token_head == NULL)
	{
		*token = token_malloc_init(NULL, nontype);
		if (!*token)
			return (1);
		*token_head = *token;
	}
	else
	{
		token_prev = *token;
		*token = token_malloc_init(NULL, nontype);
		if (!*token)
			return (1);
		token_prev->next = *token;
	}
	return (0);
}

t_token	*tokenization(t_all *all, char *s)
{
	int			i;
	int			s_len;
	t_token		*token_head;
	t_token		*token;

	token_head = NULL;
	i = 0;
	s_len = ft_strlen(s);
	while (s[i] == ' ')
		i++;
	while (i < s_len)
	{
		if (token_struct_func(&token_head, &token) == 1)
			return (token_free(token_head));
		token->str = token_str(s, &i);
		if (token->str == NULL)
			return (token_free(token_head));
	}
	token_type_func(token_head);
	if (token_redirection(&token_head) == 1)
		return (token_free(token_head));
	if (token_special(token, all) == 1)
		return (token_free(token_head));
	return (token_head);
}
