/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assemble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:13:47 by cjang             #+#    #+#             */
/*   Updated: 2022/01/10 17:23:25 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_parse	*parse_malloc_init(t_redirection *r, t_command *c, t_parse *p)
{
	t_parse		*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->left = r;
	parse->right = c;
	parse->next = p;
	return (parse);
}

t_command	*com_malloc_init(t_token *token)
{
	t_command	*command;
	t_token		*token_tmp;
	int			com_len;
	int			i;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	token_tmp = token;
	com_len = 0;
	while (token_tmp != NULL && token_tmp->type != pip)
	{
		if (token_tmp->type == com)
			com_len++;
		token_tmp = token_tmp->next;
	}
	if (com_len == 0)
		return (NULL);
	command->content = (char **)malloc((com_len + 1) * sizeof(char *));
	if (!command->content)
		return (NULL);
	token_tmp = token;
	i = 0;
	while (token_tmp != NULL && token_tmp->type != pip)
	{
		if (token_tmp->type == com)
		{
			command->content[i] = ft_strdup(token_tmp->str);
			if (command->content[i] == NULL)
			{
				while (i >= 0)
					free(command->content[i--]);
				return (NULL);
			}
			i++;
		}
		token_tmp = token_tmp->next;
	}
	command->content[i] = NULL;
	command->command = command->content[0];
	return (command);
}

t_redirection	*red_malloc_init(t_token *token)
{
	t_redirection	*red;

	red = (t_redirection *)malloc(sizeof(t_redirection));
	if (!red)
		return (NULL);
	red->next = NULL;
	red->fd_left = -1;
	if (token->type == fd_in)
	{
		red->fd_left = ft_atoi(token->str);
		token = token->next;
	}
	red->type = token->type;
	token = token->next;
	if (red->fd_left == -1)
	{
		if (red->type == r_in || red->type == r_here)
			red->fd_left = 0;
		else if (red->type == r_out || red->type == r_outapp)
			red->fd_left = 1;
	}
	if (token->type == fd_out)
	{
		red->fd_right = ft_atoi(token->str);
		red->file_name = NULL;
		token = token->next;
	}
	else if (token->type == r_file)
	{
		red->file_name = ft_strdup(token->str);
		// Free 처리 필요
		if (red->file_name == NULL)
			return (NULL);
		red->fd_right = -1;
		token = token->next;
	}
	else
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	return (red);
}

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
				return (NULL);
			if (red_head == NULL)
			{
				red_head = red_tmp;
			}
			else
			{
				red->next = red_tmp;
			}
			red = red_tmp;
			if (token->type == fd_in)
				token = token->next;
		}
		token = token->next;
	}
	return (red_head);
}

/* 해석을 완료한 token을 구조체로 구조화 시키기 */
t_parse	*parse_assemble(t_token *token_head)
{
	t_parse			*parse_head;
	t_parse			*parse;
	t_parse			*parse_tmp;
	t_token			*token;

	token = token_head;
	parse_tmp = parse_malloc_init(NULL, NULL, NULL);
	if (parse_tmp == NULL)
		return (NULL);
	parse_head = parse_tmp;
	parse = parse_tmp;
	while (token != NULL)
	{
		parse->right = com_malloc_init(token);
		parse->left = red_linked_list(token);
		while (token != NULL && token->type != pip)
			token = token->next;
		if (token != NULL)
		{
			parse_tmp = parse_malloc_init(NULL, NULL, NULL);
			if (parse_tmp == NULL)
				return (NULL);
			parse->next = parse_tmp;
			parse = parse_tmp;
			token = token->next;
		}
	}
	token_free(token_head);
	return (parse_head);
}

/* memo */
/* t_parse 개수만큼 fork() */
/* 파이프 앞-뒤 output-input 연결 */
/* 각각의 자식프로세스에 각각의 t_parse 대응시켜주기 */
/* -- 자식 프로세스 -- */
/* 리다이렉션 처리 -> open? dup2 이용*/
/* 빌트인 명령 처리 -> 구현한 빌트인인지, 아닌지 확인해서 분기 만들어주기 */
