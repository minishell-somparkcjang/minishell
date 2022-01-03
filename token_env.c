/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:02:46 by cjang             #+#    #+#             */
/*   Updated: 2022/01/02 15:20:27 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	char_delete(char *str, int *i)
{
	;
}

void	single_quote(char *str, int *i)
{
	// while (홑따옴표 찾는 함수)
		// 홑따옴표 제거
	// while (홑따옴표 찾는 함수)
		// 홑따옴표 제거 후 종료
}

void	double_quote(char *str, int *i)
{
	// while (쌍따옴표 찾는 함수)
		// 쌍따옴표 제거
	// while (쌍따옴표 or $ 찾는 함수)
		// 홑따옴표-> 제거 후 종료
		// $ -> $[환경변수이름] or $?
		// if ($[환경변수이름])
			// [\0] or 특수문자 나올때까지 확인
			// 변수 적용
}

void	env_get(char *str, int *i)
{
	if (str[*i] == '?')
	{
		return ;
	}
	else if (str[*i] >= '0' && str[*i] <= '9')
	{
		// 환경변수 가져오기
		// 바꿔끼우기
		// 환경변수 다음번째를 가리키며 끝
		return ;
	}
	else if ((str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= 'A' && str[*i] <= 'Z'))
	{
		while((str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= 'A' && str[*i] <= 'Z') || (str[*i] >= '0' && str[*i] <= '9'))
		{
			*i += 1;
		}
		// 환경변수 가져오기
		// 바꿔끼우기
		// 환경변수 다음번째를 가리키며 끝
	}
	else if (str[*i] == '\'' || str[*i] == '\"')
	{
		// $ 제거후 종료
		return ;
	}
	else
	{
		*i += 1;
		return ;
	}
}

// /* 따옴표 해석 + 환경변수 적용시키기 */
void	token_env(t_token *token)
{
	char	*s;
	char	*s_tmp;
	char	c;
	int		i;
	int		index;

	s = (char *)malloc(1 * sizeof(char));
	if (!s)
		exit(1);
	s[0] = '\0';
	while (!token)
	{
		i = 0;
		index = 0;
		while (!token->str[i])
		{
			// ['] ["] [$] 만날 때
			if (token->str[i] == '"' || token->str[i] == '\'' || token->str[i] == '$')
			{
				c = token->str[i];
				token->str[i] = '\0';
				s_tmp = s;
				s = ft_strjoin(s, &token->str[index]);
				free(s_tmp);
				token->str[i] = c;
				index = i;
				// ['] ["] [$] 이후의 파싱
				s_tmp = s;
				if (token->str[i] == '"')
				{
					s = ft_strjoin(s, double_quote(&token->str[index], i));
				}
				else if (token->str[i] == '\'')
				{
					s = ft_strjoin(s, single_quote(&token->str[index], i));
				}
				else if (token->str[i] == '$')
				{
					s = ft_strjoin(s, env_get(&token->str[index], i));
				}
				free(s_tmp);
				index = i;
			}
			i++;
		}
	}
}

// /* 해석을 완료한 token을 구조체로 구조화 시키기 */
// t_parse	*parse_assemble(t_token *token)
// {
// 	// t_parse	*parse_head;
// 	// t_parse	*parse;
// 	// t_parse	*parse_tmp;

// 	// parse_head = parse_init();
// 	// parse = parse_head;
// 	// while (!token)
// 	// {
// 	// 	if (token->type == 'c')
// 	// 		command_get();
// 	// 	else if (token->type == 'r')
// 	// 		redirection_get();
// 	// 	else if (token->type == 'p')
// 	// 	{
// 	// 		parse_tmp = parse;
// 	// 		parse = parse_init();
// 	// 		parse_tmp->next = parse;
// 	// 	}
// 	// }
// 	// // free_token() 줄줄이 토큰 free 필요
// 	// return (parse_head);
// }

// /* memo */
// /* t_parse 개수만큼 fork() */
// /* 파이프 앞-뒤 output-input 연결 */
// /* 각각의 자식프로세스에 각각의 t_parse 대응시켜주기 */
// /* -- 자식 프로세스 -- */
// /* 리다이렉션 처리 -> open? dup2 이용*/
// /* 빌트인 명령 처리 -> 구현한 빌트인인지, 아닌지 확인해서 분기 만들어주기 */
