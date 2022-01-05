/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:02:46 by cjang             #+#    #+#             */
/*   Updated: 2022/01/05 19:03:56 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	char_delete(char *str, int *i)
{
	;
}

char	*env_get(char *str, int *i, t_all *all)
{
	int		index;
	char	*str_return;
	char	*str_env;
	char	c;

	index = 0;
	// 앞 문자가 '$'가 아닌경우 예외처리
	if (str[index] != '$')
		return (NULL);
	index++;
	// $?를 지금은 임의의 수 "0"으로 리턴했지만, 실제로 이전 종료 status를 가져오고 종료할 수 있게 반영해야 함.
	if (str[*i] == '?')
	{
		str_return = ft_strdup("0");
		*i += ++index;
		if (str_return == NULL)
			exit (1);
		return (str_return);
	}
	// 숫자가 맨앞에 들어온 경우는 해당하는 숫자 하나만 환경변수 인자로 가짐.
	else if (str[*i] >= '0' && str[*i] <= '9')
	{
		index++;
		c = str[index];
		str[index] == '\0';
		str_env = find_env_key(all, &str[1]);
		if (str_env == NULL)
			str_env == "";
		str_return = ft_strdup(&str[1]);
		str[index] == c;
		*i += index;
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
	// 환경변수 메인
	else if ((str[*i] >= 'a' && str[*i] <= 'z') || \
			(str[*i] >= 'A' && str[*i] <= 'Z'))
	{
		while ((str[*i] >= 'a' && str[*i] <= 'z') || \
				(str[*i] >= 'A' && str[*i] <= 'Z') || \
				(str[*i] >= '0' && str[*i] <= '9'))
			index++;
		c = str[index];
		str[index] == '\0';
		str_env = find_env_key(all, &str[1]);
		if (str_env == NULL)
			str_env == "";
		str_return = ft_strdup(str_env);
		str[index] == c;
		*i += index;
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
	// $ 다음 따옴표가 나온 경우에는 $를 출력하지 않고 다음 따옴표를 가리키고 죵료
	else if (str[*i] == '\'' || str[*i] == '\"')
	{
		str_return = ft_strdup("");
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
	// 나머지 특수문자는 bash랑 비교해서 출력결과 세팅해야함. 여기서는 $+특수문자를 출력하게 함.
	else
	{
		index++;
		c = str[index];
		str[index] == '\0';
		str_return = ft_strdup(&str[1]);
		str[index] == c;
		*i += index;
		if (str_return == NULL)
			exit(1);
		return (str_return);
		*i += 1;
	}
}

// [']에 대한 처리, [`]는 어떻게 해야하나..
char	*single_quote(char *str, int *i)
{
	int		index;
	char	*str_return;

	index = 0;
	// 앞 문자가 [']가 아닌경우 예외처리, [`]가 아니라 [']임.
	if (str[index] != '\'')
		return (NULL);
	index++;
	// ''인 경우 ('안에 내용물 X')
	if (str[index] == '\'')
	{
		*i += ++index;
		str_return = ft_strdup("");
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
	// 따옴표 짝이 안맞는 경우 - > 예외처리 필요
	else if (str[index] == '\0')
		return (NULL);
	// 정상인 경우
	while (str[index] != '\'' || str[index] != '\0')
		index++;
	if (str[index] == '\'')
	{
		str[index] == '\0';
		str_return = ft_strdup(&str[1]);
		str[index] == '\'';
		*i += ++index;
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
}

void	double_quote(char *str, int *i)
{
	int		index;
	char	*str_return;
	char	*str_tmp;

	index = 0;
	// 앞 문자가 ["]가 아닌경우 예외처리
	if (str[index] != '"')
		return (NULL);
	index++;
	// ""인 경우 ("안에 내용물 X")
	if (str[index] == '"')
	{
		*i += ++index;
		str_return = ft_strdup("");
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
	// 따옴표 짝이 안맞는 경우 - > 예외처리 필요
	else if (str[index] == '\0')
		return (NULL);
	// 정상인 경우
	str_return = (char *)malloc(1 * sizeof(char));
	if (!str_return)
		exit(1);
	str_return[0] = '\0';
	while (str[index] != '"' || str[index] != '\0')
	{
		if (str[index] == '$')
		{
			str[index] = '\0';
			str_tmp = str_return;

			/* 진행해야 할 부분 */
			str_return = ft_strjoin(str_return, str[index]);
			free(str_tmp);
			str[index] = '$';
		}
		else
			index++;
	}
	if (str[index] == '"')
	{
		str[index] == '\0';
		str_return = ft_strdup(&str[1]);
		str[index] == '\'';
		*i += ++index;
		if (str_return == NULL)
			exit(1);
		return (str_return);
	}
}

// /* 따옴표 해석 + 환경변수 적용시키기 */
void	token_env(t_token *token, t_all *all)
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
					s = ft_strjoin(s, env_get(&token->str[index], i, all));
				}
				free(s_tmp);
				index = i;
			}
			else
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
