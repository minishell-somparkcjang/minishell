/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:17 by cjang             #+#    #+#             */
/*   Updated: 2021/12/27 18:13:00 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/* token_type 정의 */
typedef enum e_type
{
	com = 0,
	pip,
	r_in,
	r_out,
	r_outapp,
	r_here,
	r_file
}t_type;

/* readline에서 읽은 문자열을 파싱한 결과 */
typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}t_token;

/* 리다이렉션의 input_fd, 리다이렉션 타입, output_fd OR filename */
typedef struct s_redirection
{
	int				*fd_left;
	t_type			*type;
	int				*fd_right;
	char			*file_name;
}t_redirection;

/* 명령어와 인자들 */
typedef struct s_command
{
	char			*command;
	char			**content;
}t_command;

/* 파이프 단위로 linked_list */
/* 우선순위가 [리다이렉션] > [명령] 이기때문에, left->right 순으로 순회 */
typedef struct s_parse
{
	t_redirection	*left;
	t_command		*right;
	struct s_parse	*next;
}t_parse;

/* 제일 첫번째 명령이 있는 곳을 가리킴 */
typedef struct s_parse_all
{
	t_parse			*head;
}t_parse_all;

void		parse(char *str, t_all *all);
t_token		*tokenization(char *s);
void		token_init(t_token *token);
void		token_free(t_token *token_head);
int			ft_is_pos_int(char *s, int s_len, unsigned int start, unsigned int end);

#endif
