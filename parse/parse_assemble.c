/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assemble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:54:40 by cjang             #+#    #+#             */
/*   Updated: 2022/01/23 19:12:36 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redirection	*red_linked_list(t_token *token)
{
	t_redirection	*red_head;
	t_redirection	*red;
	t_redirection	*red_tmp;

	red_head = NULL;
	while (token != NULL && token->type != pip)
	{
		if (token->type == fd_in || token->type == r_in || \
		token->type == r_out || token->type == r_outapp || \
		token->type == r_here)
		{
			red_tmp = red_malloc_init(token);
			if (red_tmp == NULL)
				return (red_free(red_head));
			if (red_head == NULL)
				red_head = red_tmp;
			else
				red->next = red_tmp;
			red = red_tmp;
			if (token->type == fd_in)
				token = token->next;
		}
		token = token->next;
	}
	return (red_head);
}

static int	pip_check(t_parse **parse, t_token **token)
{
	t_parse			*parse_tmp;

	while (*token != NULL && (*token)->type != pip)
		*token = (*token)->next;
	if (*token != NULL)
	{
		parse_tmp = parse_malloc_init(NULL, NULL, NULL);
		if (parse_tmp == NULL)
			return (error_print(strerror(errno), 1));
		(*parse)->next = parse_tmp;
		*parse = parse_tmp;
		*token = (*token)->next;
	}
	return (0);
}

static int	token_to_parse(t_parse *parse_head, t_token *token)
{
	t_parse			*parse;

	parse = parse_head;
	while (token != NULL)
	{
		parse->right = NULL;
		parse->left = NULL;
		if (token_red_len(token) > 0)
		{
			parse->left = red_linked_list(token);
			if (parse->left == NULL)
				return (1);
		}
		if (token_com_len(token) > 0)
		{
			parse->right = com_malloc_init(token);
			if (parse->right == NULL)
				return (1);
		}
		if (pip_check(&parse, &token) == 1)
			return (1);
	}
	return (0);
}

t_parse	*parse_assemble(t_token *token_head, t_all *all)
{
	t_parse			*parse_head;
	t_token			*token;

	token = token_head;
	parse_head = parse_malloc_init(NULL, NULL, NULL);
	if (parse_head == NULL)
		return (error_print_null(strerror(errno), 1));
	if (token_to_parse(parse_head, token) == 1)
	{
		parse_free(parse_head);
		return (NULL);
	}
	all->pip_cnt = parse_size(parse_head);
	return (parse_head);
}
