/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:34:45 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 15:52:24 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*env_number(t_all *all, char *str, int *i, int index)
{
	char	*str_return;
	char	*str_env;
	char	c;

	index += 1;
	c = str[index];
	str[index] = '\0';
	str_env = find_env_key(all, &str[1]);
	if (str_env == NULL)
		str_env = "";
	str_return = ft_strdup_error_check(str_env);
	str[index] = c;
	*i += index;
	return (str_return);
}

static char	*env_alphabet(t_all *all, char *str, int *i, int index)
{
	char	*str_return;
	char	*str_env;
	char	c;

	while ((str[index] >= 'a' && str[index] <= 'z') || \
			(str[index] >= 'A' && str[index] <= 'Z') || \
			(str[index] >= '0' && str[index] <= '9'))
		index++;
	c = str[index];
	str[index] = '\0';
	str_env = find_env_key(all, &str[1]);
	if (str_env == NULL)
		str_env = "";
	str_return = ft_strdup_error_check(str_env);
	str[index] = c;
	*i += index;
	return (str_return);
}

static char	*env_spicial(char *str, int *i, int index)
{
	char	*str_return;
	char	c;

	index++;
	c = str[index];
	str[index] = '\0';
	str_return = ft_strdup_error_check(&str[1]);
	str[index] = c;
	*i += index;
	return (str_return);
}

char	*env_get(char *str, int *i, t_all *all)
{
	int		index;
	char	*str_return;

	index = 0;
	if (str[index] != '$')
		return (NULL);
	index++;
	if (str[index] == '?')
	{
		*i += ++index;
		str_return = ft_itoa(g_exit_code);
		return (ft_strdup_error_check(str_return));
	}
	else if (str[index] >= '0' && str[index] <= '9')
		return (env_number(all, str, i, index));
	else if ((str[index] >= 'a' && str[index] <= 'z') || \
			(str[index] >= 'A' && str[index] <= 'Z'))
		return (env_alphabet(all, str, i, index));
	else if (str[index] == '\'' || str[index] == '\"')
		return (ft_strdup_error_check(""));
	else
		return (env_spicial(str, i, index));
}
