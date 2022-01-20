/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:00:12 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 18:00:26 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_init(t_token *token, char *str, t_token *next)
{
	token->str = str;
	token->next = next;
}

t_token	*token_malloc_init(char *str, t_type type)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (error_print_null(strerror(errno), 1));
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}
