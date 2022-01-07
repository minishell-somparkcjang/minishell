/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assemble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:13:47 by cjang             #+#    #+#             */
/*   Updated: 2022/01/06 16:17:55 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_parse	parse_init(void)
{
	(void) ;
}

/* 해석을 완료한 token을 구조체로 구조화 시키기 */
t_parse	*parse_assemble(t_token *token)
{
	t_parse		*parse_head;
	t_parse		*parse;
	t_parse		*parse_tmp;

	parse_head = parse_init();
	parse = parse_head;
	while (!token)
	{
		if (token->type == 'c')
			command_get();
		else if (token->type == 'r')
			redirection_get();
		else if (token->type == 'p')
		{
			parse_tmp = parse;
			parse = parse_init();
			parse_tmp->next = parse;
		}
	}
	// free_token() 줄줄이 토큰 free 필요
	return (parse_head);
}

/* memo */
/* t_parse 개수만큼 fork() */
/* 파이프 앞-뒤 output-input 연결 */
/* 각각의 자식프로세스에 각각의 t_parse 대응시켜주기 */
/* -- 자식 프로세스 -- */
/* 리다이렉션 처리 -> open? dup2 이용*/
/* 빌트인 명령 처리 -> 구현한 빌트인인지, 아닌지 확인해서 분기 만들어주기 */
