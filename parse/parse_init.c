/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:01:48 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 18:37:06 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parse	*parse_malloc_init(t_redirection *r, t_command *c, t_parse *p)
{
	t_parse		*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	if (!parse)
		return (error_print_null(strerror(errno), 1));
	parse->left = r;
	parse->right = c;
	parse->next = p;
	return (parse);
}

static int	com_con_malloc_init(t_command *comm, t_token *token, int com_len)
{
	int			i;

	i = 0;
	comm->content = (char **)malloc((com_len + 1) * sizeof(char *));
	if (!comm->content)
		return (error_print(strerror(errno), 1));
	while (token != NULL && token->type != pip)
	{
		if (token->type == com)
		{
			comm->content[i] = ft_strdup_error_check(token->str);
			if (comm->content[i] == NULL)
			{
				while (i >= 0)
					free(comm->content[i--]);
				free(comm->content);
				return (1);
			}
			i++;
		}
		token = token->next;
	}
	comm->content[i] = NULL;
	return (0);
}

t_command	*com_malloc_init(t_token *token)
{
	t_command	*command;
	int			com_len;

	com_len = token_com_len(token);
	if (com_len == 0)
		return (NULL);
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (error_print_null(strerror(errno), 1));
	command->command = NULL;
	command->content = (char **)malloc((com_len + 1) * sizeof(char *));
	if (!command->content)
		return (error_print_null(strerror(errno), 1));
	if (com_con_malloc_init(command, token, com_len) == 1)
	{
		free(command);
		return (NULL);
	}
	command->command = command->content[0];
	return (command);
}

static int	red_fdout_file_check(t_redirection *red, t_token *token)
{
	if (token != NULL && token->type == fd_out)
	{
		red->fd_right = ft_atoi(token->str);
		red->file_name = NULL;
		token = token->next;
	}
	else if (token != NULL && token->type == r_file)
	{
		red->file_name = ft_strdup_error_check(token->str);
		if (red->file_name == NULL)
			return (1);
		red->fd_right = -1;
		token = token->next;
	}
	else
		return (error_print("minishell: \
		syntax error near unexpected token `newline'", 1));
	return (0);
}

t_redirection	*red_malloc_init(t_token *token)
{
	t_redirection	*red;

	red = (t_redirection *)malloc(sizeof(t_redirection));
	if (!red)
		return (error_print_null(strerror(errno), 1));
	red->next = NULL;
	red->fd_left = -1;
	if (token->type == fd_in)
	{
		red->fd_left = ft_atoi(token->str);
		token = token->next;
	}
	red->type = token->type;
	token = token->next;
	if (red->fd_left == -1 && (red->type == r_in || red->type == r_here))
		red->fd_left = 0;
	else if (red->fd_left == -1 && \
	(red->type == r_out || red->type == r_outapp))
		red->fd_left = 1;
	if (red_fdout_file_check(red, token) == 1)
	{
		free(red);
		return (NULL);
	}
	return (red);
}
