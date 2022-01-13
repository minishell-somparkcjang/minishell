/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:21:31 by cjang             #+#    #+#             */
/*   Updated: 2022/01/07 18:52:08 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	token_init(t_token *token, char *str, t_token *next)
{
	token->str = str;
	token->next = next;
}

void	token_free(t_token *token_head)
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
}

t_token	*token_malloc_init(char *str, t_type type)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
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
