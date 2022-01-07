/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:12 by cjang             #+#    #+#             */
/*   Updated: 2022/01/07 18:46:12 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	print_token(t_token *token)
{
	char	*type;

	while (token != NULL)
	{
		if (token->type == com)
			type = "com";
		else if (token->type == pip)
			type = "pip";
		else if (token->type == r_in)
			type = "r_in";
		else if (token->type == r_out)
			type = "r_out";
		else if (token->type == r_outapp)
			type = "r_outapp";
		else if (token->type == r_here)
			type = "r_here";
		else if (token->type == fd_in)
			type = "fd_in";
		else if (token->type == fd_out)
			type = "fd_out";
		else if (token->type == r_file)
			type = "r_file";
		printf("[%s]<%s>	", token->str, type);
		token = token->next;
	}
	printf("\n");
}

void	parse_main(char *s, t_all *all)
{
	t_token		*token_head;

	// 따옴표 짝에 대한 체크를 따로 할지, 아니면 구조체를 형성하는 과정에서 할지 고민요소
	token_head = tokenization(s);
	if (token_head == NULL)
		return ;
	token_env(token_head, all);
	if (token_head == NULL)
		return ;
	print_token(token_head);
}
