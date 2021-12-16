/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:57:17 by cjang             #+#    #+#             */
/*   Updated: 2021/12/16 15:47:00 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// flag - '' "" 체크
typedef struct s_content
{
	char				*content;
	char				*flag;
	struct s_content	*next;
}t_content;

// flag - Redirections, Pipes 체크
// Redirections, Pipes를 기준으로 나눔
typedef struct s_parse
{
	char			*command;
	char			*option;
	char			*flag;
	struct s_parse	*next;
	t_content		*head;
}t_parse;

typedef struct s_parse_all
{
	t_parse			*head;
}t_parse_all;

void	parse(char *str, t_all *all);

#endif
