/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:03:29 by cjang             #+#    #+#             */
/*   Updated: 2022/01/24 22:39:46 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*type_check(t_type type)
{
	char	*str;

	if (type == com)
		str = "com";
	else if (type == pip)
		str = "pip";
	else if (type == r_in)
		str = "r_in";
	else if (type == r_out)
		str = "r_out";
	else if (type == r_outapp)
		str = "r_outapp";
	else if (type == r_here)
		str = "r_here";
	else if (type == fd_in)
		str = "fd_in";
	else if (type == fd_out)
		str = "fd_out";
	else if (type == r_file)
		str = "r_file";
	else
		str = "nontype";
	return (str);
}

void	print_token(t_token *token)
{
	char	*type;

	while (token != NULL)
	{
		type = type_check(token->type);
		printf("[%s]<%s>	", token->str, type);
		token = token->next;
	}
	printf("\n");
}

static void	print_red(t_redirection *red)
{
	char			*type;

	while (red != NULL)
	{
		type = type_check(red->type);
		printf("	[red]	[%d][%s][%d][%s]\n", \
		red->fd_left, type, red->fd_right, red->file_name);
		red = red->next;
	}	
}

void	print_parse(t_parse *parse)
{
	t_command		*com;
	int				i;
	char			**str;

	i = 0;
	while (parse != NULL)
	{
		printf("[par][%d]\n", i++);
		com = parse->right;
		print_red(parse->left);
		if (com != NULL)
		{
			printf("	[com]	[%s]: ", com->command);
			str = com->content;
			while (*str != NULL)
			{
				printf("[%s]", *str);
				str++;
			}
			printf("\n");
		}
		parse = parse->next;
	}
}

void	parse_main(char *s, t_all *all)
{
	t_token		*token_head;
	t_parse		*parse_head;

	all->parser = NULL;
	token_head = tokenization(all, s);
	if (token_head == NULL)
		return ;
	parse_head = parse_assemble(token_head, all);
	if (parse_head == NULL)
	{
		token_free(token_head);
		return ;
	}
	token_free(token_head);
	all->parser = parse_head;
}
