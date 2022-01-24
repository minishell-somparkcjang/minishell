/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:08:23 by cjang             #+#    #+#             */
/*   Updated: 2022/01/24 14:46:48 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*single_quote(char *str, int *i)
{
	int		index;
	char	*str_return;

	index = 0;
	if (str[index] != '\'')
		return (NULL);
	index++;
	if (str[index] == '\'')
	{
		*i += ++index;
		return (ft_strdup_error_check(""));
	}
	while (str[index] != '\'' && str[index] != '\0')
		index++;
	if (str[index] == '\'')
	{
		str[index] = '\0';
		str_return = ft_strdup_error_check(&str[1]);
		str[index] = '\'';
		*i += ++index;
		return (str_return);
	}
	else
		return (error_print_null("please write another ['].", 1));
}

static char	*dq_in_env(t_all *all, char *str, char *str_return, int *index)
{
	char	*str_tmp;
	char	*str_tmp2;

	str[index[0]] = '\0';
	str_tmp = str_return;
	str_return = ft_strjoin(str_return, &str[index[1]]);
	free(str_tmp);
	if (str_return == NULL)
		return (error_print_null(strerror(errno), 1));
	str[*index] = '$';
	str_tmp2 = env_get(&str[index[0]], &index[0], all);
	if (str_tmp2 == NULL)
		return (error_print_null(strerror(errno), 1));
	str_tmp = str_return;
	str_return = ft_strjoin(str_return, str_tmp2);
	if (str_return == NULL)
		return (error_print_null(strerror(errno), 1));
	free(str_tmp);
	free(str_tmp2);
	index[1] = index[0];
	return (str_return);
}

static char	*dq_pair_check(char *str, char *str_return, int *i, int *index)
{
	char	*str_tmp;

	if (str[index[0]] == '"')
	{
		str[index[0]] = '\0';
		str_tmp = str_return;
		str_return = ft_strjoin(str_return, &str[index[1]]);
		free(str_tmp);
		str[index[0]] = '"';
		*i += ++index[0];
		if (str_return == NULL)
			return (error_print_null(strerror(errno), 1));
		return (str_return);
	}
	else
		return (error_print_null("please write another [\"].", 1));
}

static char	*dq_check_init(char *str, int *i, int *index)
{
	char	*str_return;

	index[0] = 0;
	if (str[index[0]] != '"')
		return (NULL);
	index[0]++;
	if (str[index[0]] == '"')
	{
		*i += ++index[0];
		return (ft_strdup_error_check(""));
	}
	str_return = (char *)malloc(1 * sizeof(char));
	if (str_return == NULL)
		return (error_print_null(strerror(errno), 1));
	str_return[0] = '\0';
	index[1] = index[0];
	return (str_return);
}

char	*double_quote(char *str, int *i, t_all *all)
{
	int		index[2];
	char	*str_return;

	str_return = dq_check_init(str, i, index);
	if (str_return == NULL)
		return (NULL);
	else if (str[0] == '"' && str[1] == '"')
		return (str_return);
	while (str[index[0]] != '"' && str[index[0]] != '\0')
	{
		if (str[index[0]] == '$')
		{
			str_return = dq_in_env(all, str, str_return, index);
			if (str_return == NULL)
				return (NULL);
		}
		else
			index[0]++;
	}
	str_return = dq_pair_check(str, str_return, i, index);
	return (str_return);
}
