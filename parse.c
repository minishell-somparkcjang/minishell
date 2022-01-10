/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:12 by cjang             #+#    #+#             */
/*   Updated: 2022/01/10 17:25:30 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*type_check(t_type type)
{
	char	*str;

	if (type == com)
		str = "com";
	else if (type == pip)
		str = "pip";
	else if (type == r_in)
		str = "r_in";
	else if (type == r_out)
		str = "r_out";
	else if (type == r_outapp)
		str = "r_outapp";
	else if (type == r_here)
		str = "r_here";
	else if (type == fd_in)
		str = "fd_in";
	else if (type == fd_out)
		str = "fd_out";
	else if (type == r_file)
		str = "r_file";
	return (str);
}

static void	print_token(t_token *token)
{
	char	*type;

	while (token != NULL)
	{
		type = type_check(token->type);
		printf("[%s]<%s>	", token->str, type);
		token = token->next;
	}
	printf("\n");
}

static void	print_parse(t_parse *parse)
{
	t_redirection	*red;
	t_command		*com;
	int				i;
	char			*type;
	char			**str;

	i = 0;
	while (parse != NULL)
	{
		printf("[par][%d]\n", i++);
		red = parse->left;
		com = parse->right;
		while (red != NULL)
		{
			type = type_check(red->type);
			printf("[red]	[%d][%s][%d][%s]\n", red->fd_left, type, red->fd_right, red->file_name);
			red = red->next;
		}
		if (com != NULL)
		{
			printf("[com]	[%s]: ", com->command);
			str = com->content;
			while (*str != NULL)
			{
				printf("[%s]", *str);
				str++;
			}
			printf("\n");
		}
		parse = parse->next;
	}
}
void	parse_main(char *s, t_all *all)
{
	t_token		*token_head;
	t_parse		*parse_head;

	// 따옴표 짝에 대한 체크를 따로 할지, 아니면 구조체를 형성하는 과정에서 할지 고민요소
	token_head = tokenization(s);
	if (token_head == NULL)
		return ;
	token_env(token_head, all);
	if (token_head == NULL)
		return ;
	print_token(token_head);
	parse_head = parse_assemble(token_head);
	if (parse_head == NULL)
		return ;
	print_parse(parse_head);
}
