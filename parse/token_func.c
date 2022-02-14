/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:57:40 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 18:03:17 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_free(t_token *token_head)
{
	t_token		*token;
	t_token		*token_tmp;

	token = token_head;
	while (token != NULL)
	{
		if (token->str != NULL)
			free(token->str);
		token_tmp = token;
		token = token->next;
		free(token_tmp);
	}
	return (NULL);
}

t_token	*token_head_insert(t_token *token_head, t_token *token_new)
{
	token_new->next = token_head;
	return (token_new);
}

void	token_insert(t_token *token, t_token *token_new)
{
	token_new->next = token->next;
	token->next = token_new;
}

int	token_com_len(t_token *token)
{
	int			com_len;

	com_len = 0;
	while (token != NULL && token->type != pip)
	{
		if (token->type == com)
			com_len++;
		token = token->next;
	}
	return (com_len);
}

int	token_red_len(t_token *token)
{
	int			red_len;

	red_len = 0;
	while (token != NULL && token->type != pip)
	{
		if (token->type == r_in || token->type == r_out || \
		token->type == r_outapp || token->type == r_here)
			red_len++;
		token = token->next;
	}
	return (red_len);
}
