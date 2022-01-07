/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:02:46 by cjang             #+#    #+#             */
/*   Updated: 2022/01/06 16:13:52 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
	if (str[index] == '?')
	{
		*i += ++index;
		return (ft_strdup("0"));
	}
	// 숫자가 맨앞에 들어온 경우는 해당하는 숫자 하나만 환경변수 인자로 가짐.
	else if (str[index] >= '0' && str[index] <= '9')
	{
		index++;
		c = str[index];
		str[index] = '\0';
		str_env = find_env_key(all, &str[1]);
		if (str_env == NULL)
			str_env = "";
		str_return = ft_strdup(&str[1]);
		str[index] = c;
		*i += index;
		return (str_return);
	}
	// 환경변수 메인
	else if ((str[index] >= 'a' && str[index] <= 'z') || \
			(str[index] >= 'A' && str[index] <= 'Z'))
	{
		while ((str[index] >= 'a' && str[index] <= 'z') || \
				(str[index] >= 'A' && str[index] <= 'Z') || \
				(str[index] >= '0' && str[index] <= '9'))
			index++;
		c = str[index];
		str[index] = '\0';
		str_env = find_env_key(all, &str[1]);
		if (str_env == NULL)
			str_env = "";
		str_return = ft_strdup(str_env);
		str[index] = c;
		*i += index;
		return (str_return);
	}
	// $ 다음 따옴표가 나온 경우에는 $를 출력하지 않고 다음 따옴표를 가리키고 죵료
	else if (str[index] == '\'' || str[index] == '\"')
	{
		str_return = ft_strdup("");
		return (str_return);
	}
	// 나머지 특수문자는 bash랑 비교해서 출력결과 세팅해야함. 여기서는 $+특수문자를 출력하게 함.
	else
	{
		index++;
		c = str[index];
		str[index] = '\0';
		str_return = ft_strdup(&str[1]);
		str[index] = c;
		*i += index;
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
		return (ft_strdup(""));
	}
	// 정상인 경우
	while (str[index] != '\'' && str[index] != '\0')
		index++;
	if (str[index] == '\'')
	{
		str[index] = '\0';
		str_return = ft_strdup(&str[1]);
		str[index] = '\'';
		*i += ++index;
		return (str_return);
	}
	// 따옴표 짝이 안맞는 경우 - > 예외처리 필요
	else
	{
		printf("please write another ['].\n");
		exit(1);
	}
}

char	*double_quote(char *str, int *i, t_all *all)
{
	int		index;
	int		index_tmp;
	char	*str_return;
	char	*str_tmp;
	char	*str_tmp2;

	index = 0;
	// 앞 문자가 ["]가 아닌경우 예외처리
	if (str[index] != '"')
		return (NULL);
	index++;
	// ""인 경우 ("안에 내용물 X")
	if (str[index] == '"')
	{
		*i += ++index;
		return (ft_strdup(""));
	}
	// 정상인 경우
	str_return = (char *)malloc(1 * sizeof(char));
	if (str_return == NULL)
		return (NULL);
	str_return[0] = '\0';
	index_tmp = index;
	while (str[index] != '"' && str[index] != '\0')
	{
		if (str[index] == '$')
		{
			str[index] = '\0';
			str_tmp = str_return;
			str_return = ft_strjoin(str_return, &str[index_tmp]);
			free(str_tmp);
			if (str_return == NULL)
				return (NULL);
			str[index] = '$';
			str_tmp2 = env_get(&str[index], &index, all);
			if (str_tmp2 == NULL)
				return (NULL);
			str_tmp = str_return;
			str_return = ft_strjoin(str_return, str_tmp2);
			if (str_return == NULL)
				return (NULL);
			free(str_tmp);
			free(str_tmp2);
			index_tmp = index;
		}
		else
			index++;
	}
	if (str[index] == '"')
	{
		str[index] = '\0';
		str_tmp = str_return;
		str_return = ft_strjoin(str_return, &str[index_tmp]);
		free(str_tmp);
		str[index] = '"';
		*i += ++index;
		return (str_return);
	}
	// 따옴표 짝이 안맞는 경우 - > 예외처리 필요
	else
	{
		printf("please write another [\"].\n");
		exit(1);
	}
}

/* 따옴표 해석 + 환경변수 적용시키기 */
void	token_env(t_token *token, t_all *all)
{
	char	*s;
	char	*s_tmp;
	char	*s_tmp2;
	char	c;
	int		i;
	int		index;

	while (token != NULL)
	{
		s = (char *)malloc(1 * sizeof(char));
		if (!s)
			exit(1);
		s[0] = '\0';
		i = 0;
		index = 0;
		while (token->str[i] != '\0')
		{
			// ['] ["] [$] 만날 때
			if (token->str[i] == '"' || token->str[i] == '\'' || token->str[i] == '$')
			{
				c = token->str[i];
				token->str[i] = '\0';
				s_tmp = s;
				s = ft_strjoin(s, &token->str[index]);
				if (s == NULL)
					exit(1);
				free(s_tmp);
				token->str[i] = c;
				index = i;
				// ['] ["] [$] 이후의 파싱
				s_tmp = s;
				if (token->str[i] == '"')
					s_tmp2 = double_quote(&token->str[index], &i, all);
				else if (token->str[i] == '\'')
					s_tmp2 = single_quote(&token->str[index], &i);
				else if (token->str[i] == '$')
					s_tmp2 = env_get(&token->str[index], &i, all);
				if (s_tmp2 == NULL)
					exit(1);
				s = ft_strjoin(s, s_tmp2);
				free(s_tmp);
				free(s_tmp2);
				index = i;
			}
			else
				i++;
		}
		if (index == 0)
			free(s);
		else
		{
			s_tmp = s;
			s = ft_strjoin(s, &token->str[index]);
			if (s == NULL)
				exit(1);
			free(s_tmp);
			free(token->str);
			token->str = s;
		}
		token = token->next;
	}
}
