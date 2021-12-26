/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:21:31 by cjang             #+#    #+#             */
/*   Updated: 2021/12/26 17:21:33 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	token_init(t_token *token)
{
	token->str = NULL;
	token->next = NULL;
}

void	token_free(t_token *token_head)
{
	t_token		*token;

	token = token_head;
	while (token != NULL)
	{
		if (token->str != NULL)
			free(token->str);
		token = token->next;
		free(token);
	}
}
