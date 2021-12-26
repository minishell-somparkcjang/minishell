/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:17 by cjang             #+#    #+#             */
/*   Updated: 2021/12/26 17:21:47 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// split한 결과물
typedef struct s_token
{
	char			*str;
	char			type;
	struct s_token	*next;
}t_token;

// 1> outfile // cat <2
typedef struct s_redirection
{
	int				*fd_left;
	char			*type;
	int				*fd_right;
	char			*file_name;
}t_redirection;

// '' ""와 안의 $는 해석 후에 넣기
typedef struct s_command
{
	char			*command;
	char			**content;
}t_command;

// Pipes를 기준으로 나눔
typedef struct s_parse
{
	t_redirection	*left;
	t_command		*right;
	struct s_parse	*next;
}t_parse;

typedef struct s_parse_all
{
	t_parse			*head;
}t_parse_all;

void		parse(char *str, t_all *all);
t_token		*tokenization(char *s);
void		token_init(t_token *token);
void		token_free(t_token *token_head);

#endif
