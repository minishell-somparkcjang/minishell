/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:57:40 by cjang             #+#    #+#             */
/*   Updated: 2022/01/19 16:57:40 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_init(t_token *token, char *str, t_token *next)
{
	token->str = str;
	token->next = next;
}

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

t_token	*token_malloc_init(char *str, t_type type)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		error_print(strerror(errno), 1);
		return (NULL);
	}
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
