/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:59:15 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 18:35:15 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*red_free(t_redirection *red)
{
	t_redirection	*red_prev;

	while (red != NULL)
	{
		if (red->file_name != NULL)
			free(red->file_name);
		red_prev = red;
		red = red->next;
		free(red_prev);
	}
	return (NULL);
}

static void	com_free(t_command *com)
{
	int				i;

	i = 0;
	if (com != NULL)
	{
		while (com->content[i] != NULL)
		{
			free(com->content[i]);
			i++;
		}
		free(com->content);
		free(com);
	}
}

void	parse_free(t_parse *parse_head)
{
	t_parse			*parse;
	t_parse			*parse_prev;

	parse = parse_head;
	while (parse != NULL)
	{
		red_free(parse->left);
		com_free(parse->right);
		parse_prev = parse;
		parse = parse->next;
		free(parse_prev);
	}
	parse_head = NULL;
}

int	parse_size(t_parse *parse_head)
{
	int		len;
	t_parse	*parse;

	len = 0;
	parse = parse_head;
	while (parse)
	{
		len++;
		parse = parse->next;
	}
	return (len);
}
