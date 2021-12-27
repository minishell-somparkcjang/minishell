/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:31:24 by cjang             #+#    #+#             */
/*   Updated: 2021/12/27 18:12:38 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* 큰 틀에서 구성해봄, 세부함수는 아직 x */

/* readline으로 받아온 문자열을 bash 인자 기준에 맞게 쪼갬 */
/* 쪼갠 인자들의 타입이 무엇인지 char형으로 체크(c ommand, p ip, r edirection) */

static char	*token_str_return(char *s, int i_tmp, int *i)
{
	char	c;
	char	*str;

	c = s[*i];
	s[*i] = '\0';
	str = ft_strdup(&s[i_tmp]);
	s[*i] = c;
	return (str);
}

static char	*token_str(char *s, int *i)
{
	int		i_tmp;
	int		quotes_flag;
	int		redi_flag;

	quotes_flag = 0;
	redi_flag = 0;
	i_tmp = *i;
	/* 맨 앞 문자가 [|]인 경우 [|]만 파싱 하기 */
	if (s[*i] == '|')
	{
		*i += 1;
		while (s[*i] == ' ')
			*i += 1;
		return (ft_strdup("|"));
	}
	/* [|] [ ] [\0] 이 나올 때 까지 진행 */
	/* [" "] [' '] 안에 있는 [ ] [|] 는 만나도 계속 진행 */
	while (((s[*i] != '|' && s[*i] != ' ') || quotes_flag != 0) \
	&& s[*i] != '\0')
	{
		if (s[*i] == '\'' && quotes_flag == 0)
			quotes_flag = 1;
		else if (s[*i] == '\"' && quotes_flag == 0)
			quotes_flag = 2;
		else if (s[*i] == '\'' && quotes_flag == 1)
			quotes_flag = 0;
		else if (s[*i] == '\"' && quotes_flag == 2)
			quotes_flag = 0;
		else if ((s[*i] == '<' || s[*i] == '>') && redi_flag == 0)
		{
			if (ft_is_pos_int(&s[i_tmp], *i - i_tmp, 0, 0x7FFFFFFF) == 0)
				return (token_str_return(s, i_tmp, i));
			else
			{
				if (s[*i] == s[*i + 1])
					*i += 1;
				redi_flag = 1;
			}	
		}
		else if ((s[*i] == '<' || s[*i] == '>') && redi_flag == 1)
			return (token_str_return(s, i_tmp, i));
		*i += 1;
	}
	/* 가리키는 끝 문자가 [ ]인 경우 [ ]가 없을때까지 i값 증가 */
	if (s[*i] == ' ')
	{
		s[*i] = '\0';
		*i += 1;
		while (s[*i] == ' ')
			*i += 1;
		return (ft_strdup(&s[i_tmp]));
	}
	/* 가리키는 끝 문자가 [|]인 경우 [|] 앞에서 끊어줌 */
	/* hello|		-> hello만 파싱 */
	else if (s[*i] == '|')
		return (token_str_return(s, i_tmp, i));
	/* 가리키는 끝 문자가 [\0]인 경우 그대로 dup */
	else
		return (ft_strdup(&s[i_tmp]));

}

static t_type	token_type(t_token *token_prev, t_token *token)
{
	int		i;
	int		quotes_flag;
	char	*s;
	t_type	t;

	(void)token_prev ;
	i = 0;
	quotes_flag = 0;
	s =token->str;
	while (((s[i] != '|' && s[i] != '<' && s[i] != '>') || quotes_flag != 0) \
	&& s[i] != '\0')
	{
		if (s[i] == '\'' && quotes_flag == 0)
			quotes_flag = 1;
		else if (s[i] == '\"' && quotes_flag == 0)
			quotes_flag = 2;
		else if (s[i] == '\'' && quotes_flag == 1)
			quotes_flag = 0;
		else if (s[i] == '\"' && quotes_flag == 2)
			quotes_flag = 0;
		i++;
	}
	if (s[i] == '|')
		t = pip;
	else if (s[i] == '<')
		t = r_in;
	else if (s[i] == '>')
		t = r_out;
	// else if (token_prev->type == 'r')
	// {
	// 	c = token_prev->str[ft_strlen(token_prev->str) - 1];
	// 	/* 리다이렉션 예외처리 필요 */
	// 	return ('r');
	// }
	else
		t = com;
	return (t);
}

t_token	*tokenization(char *s)
{
	int		i;
	int		s_len;
	t_token	*token_head;
	t_token	*token;
	t_token *token_prev;

	i = 0;
	s_len = ft_strlen(s);
	token_head = NULL;
	/* string 파싱 */
	while (s[i] == ' ')
		i++;
	while (i < s_len)
	{
		if (token_head == NULL)
		{
			token = (t_token *)malloc(sizeof(t_token));
			token_init(token);
			if (!token)
				return (NULL);
			token_head = token;
		}
		else
		{
			token_prev = token;
			token = (t_token *)malloc(sizeof(t_token));
			token_init(token);
			if (!token)
				return (NULL);
			token_prev->next = token;
		}
		token->str = token_str(s, &i);
		// printf("%s\n", token->str);
		/* token->str에서 할당이 제대로 안 이루어질 경우 */
		if (token->str == NULL)
		{
			token_free(token_head);
			return (NULL);
		}
	}

	/* command, redirection, pip type 체크 */
	token = token_head;
	token_prev = NULL;
	while (token != NULL)
	{
		token->type = token_type(token_prev, token);
		token_prev = token;
		token = token->next;
	}
	token = token_head;
	while (token != NULL)
	{
		printf("[%s]%d	", token->str, token->type);
		token = token->next;
	}
	printf("\n");
	return (token_head);
}
