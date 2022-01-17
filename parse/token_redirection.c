/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:01:11 by cjang             #+#    #+#             */
/*   Updated: 2022/01/18 01:07:24 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_redirection(t_token **token_head)
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
				token_new = token_malloc_init(str_split[0], fd_in, NULL);
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
						token_new = token_malloc_init(str_split[2], r_file, NULL);
					else if (0 <= i_check && i_check <= 10)
						token_new = token_malloc_init(str_split[2], fd_out, NULL);
					else
					{
						printf("bash: %d: Bad file descriptor\n", i_check);
						return (1);
					}
				}
				else
					token_new = token_malloc_init(str_split[2], r_file, NULL);
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
