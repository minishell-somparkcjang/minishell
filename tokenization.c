/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:31:24 by cjang             #+#    #+#             */
/*   Updated: 2022/01/07 18:52:22 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* token_str용 함수 */
static char	*token_str_return(char *s, int i_start, int i_end)
{
	char	c;
	char	*str;

	c = s[i_end];
	s[i_end] = '\0';
	str = ft_strdup(&s[i_start]);
	s[i_end] = c;
	return (str);
}

/* 구체적인 문자열 토큰화하는 부분 */
static char	*token_str(char *s, int *i)
{
	int		i_tmp;
	int		quotes_flag;
	int		redi_flag;
	int		i_check;

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
	/* [<] [>]는 while문 안에서 따로 처리 */
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
		else if ((s[*i] == '<' || s[*i] == '>') && redi_flag == 0 && quotes_flag == 0)
		{
			// [-2] 문자 포함
			// [-1] 2^31~ -> bash: file descriptor out of range: Bad file descriptor
			// [num] 0~255 -> 파일 디스크립터로 ok
			// [num] 256~2^31-1 ->  Bad file descriptor
			i_check = ft_is_fd_range(&s[i_tmp], *i - i_tmp);
			if (*i != i_tmp && i_check == -2)
				return (token_str_return(s, i_tmp, *i));
			// 에러처리 (보완필요)
			else if (*i != i_tmp && 256 <= i_check && i_check <= 0x7FFFFFFF)
			{
				printf("bash: %d: Bad file descriptor\n", i_check);
				return (NULL);
			}
			else if (*i != i_tmp && i_check == -1)
			{
				printf("bash: file descriptor out of range: Bad file descriptor\n");
				return (NULL);
			}
			else
			{
				if (s[*i] == s[*i + 1])
					*i += 1;
				redi_flag = 1;
			}	
		}
		else if ((s[*i] == '<' || s[*i] == '>') && redi_flag == 1)
			return (token_str_return(s, i_tmp, *i));
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
		return (token_str_return(s, i_tmp, *i));
	/* 가리키는 끝 문자가 [\0]인 경우 그대로 dup */
	else
		return (ft_strdup(&s[i_tmp]));
}

/* token화 한 문자열의 타입 체크하기 */
static t_type	token_type(t_token *token_prev, t_token *token)
{
	int		i;
	int		quotes_flag;
	char	*s;
	t_type	t;

	i = 0;
	quotes_flag = 0;
	s = token->str;
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
	else if (s[i] == '<' && s[i + 1] == '<')
		t = r_here;
	else if (s[i] == '>' && s[i + 1] == '>')
		t = r_outapp;
	else if (s[i] == '<')
		t = r_in;
	else if (s[i] == '>')
		t = r_out;
	else if (token_prev != NULL && ft_strlen(token_prev->str) > 0)
	{
		s = token_prev->str;
		if (s[ft_strlen(s) - 1] == '<' || s[ft_strlen(s) - 1] == '>')
			t = r_file;
		else
			t = com;
	}
	else
		t = com;
	return (t);
}

static int	token_split_redi(t_token **token_head)
{
	t_token		*token_prev;
	t_token		*token;
	t_token		*token_new;
	char		*str_tmp;
	char		*str_split[3];
	char		c;
	int			i;
	int			i_start;
	int			i_check;

	token_prev = NULL;
	token = *token_head;
	while (token != NULL)
	{
		i = 0;
		i_start = 0;
		str_split[0] = NULL;
		str_split[1] = NULL;
		str_split[2] = NULL;
		if (token->type == r_in || token->type == r_out || \
			token->type == r_outapp || token->type == r_here)
		{
			/* 타입이 단지 < > << >> 면 나눌 필요 x */
			// fd_in
			if (token->str[i] >= '0' && token->str[i] <= '9')
			{
				while (token->str[i] != '<' && token->str[i] != '>')
					i++;
				str_split[0] = token_str_return(token->str, i_start, i);
				if (str_split[0] == NULL)
					exit(1);
				i_start = i;
			}
			// redirection type
			while (token->str[i] == '<' || token->str[i] == '>')
				i++;
			str_split[1] = token_str_return(token->str, i_start, i);
			if (str_split[1] == NULL)
				exit(1);
			i_start = i;
			// fd_out
			if (token->str[i] != '\0')
			{
				while (token->str[i] != '\0')
					i++;
				str_split[2] = token_str_return(token->str, i_start, i);
				if (str_split[2] == NULL)
					exit(1);
			}
			// fd_in
			if (str_split[0] != NULL)
			{
				token_new = token_malloc_init(str_split[0], fd_in);
				if (token_new == NULL)
					exit(1);
				if (token_prev == NULL)
					*token_head = token_head_insert(token, token_new);
				else
					token_insert(token_prev, token_new);
				token_prev = token_new;
			}
			// redirection type
			free(token->str);
			token->str = str_split[1];
			// fd_out
			if (str_split[2] != NULL)
			{
				if (str_split[2][0] == '&')
				{
					str_tmp = ft_strdup(&str_split[2][1]);
					if (str_tmp == NULL)
						exit(1);
					free(str_split[2]);
					str_split[2] = str_tmp;
					i_check = ft_is_fd_range(str_split[2], ft_strlen(str_split[2]));
					if (i_check == -2)
						token_new = token_malloc_init(str_split[2], r_file);
					else if (0 <= i_check && i_check <= 10)
						token_new = token_malloc_init(str_split[2], fd_out);
					else
					{
						printf("bash: %d: Bad file descriptor\n", i_check);
						return (1);
					}
				}
				else
					token_new = token_malloc_init(str_split[2], r_file);
				if (token_new == NULL)
					exit(1);
				token_insert(token, token_new);
				token_prev = token;
				token = token_new;
			}
		}
		token_prev = token;
		token = token->next;
	}
	return (0);
}

/* readline으로 받은 문자열을 띄어쓰기 단위로 token화 하기 */
t_token	*tokenization(char *s)
{
	int		i;
	int		s_len;
	t_token	*token_head;
	t_token	*token;
	t_token	*token_prev;

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
			token = token_malloc_init(NULL, nontype);
			if (!token)
				return (NULL);
			token_head = token;
		}
		else
		{
			token_prev = token;
			token = token_malloc_init(NULL, nontype);
			if (!token)
				return (NULL);
			token_prev->next = token;
		}
		token->str = token_str(s, &i);
		// printf ("[%s]\n", token->str);
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
	i = token_split_redi(&token_head);
	if (i == 1)
	{
		token_free(token_head);
		return (NULL);
	}
	return (token_head);
}
