/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:15 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 12:12:25 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_equal(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	set_env(char *content, t_all *all)
{
	int		idx;
	int		len;
	char	*value;
	char	*key;

	idx = is_equal(content);
	if (idx == -1)
	{
		value = find_env_key(all, content);
		if (!value)
			set_env_value(all, ft_strdup(content), NULL);
	}
	else
	{
		len = ft_strlen(content);
		key = ft_substr(content, 0, idx);
		value = ft_substr(content, idx + 1, len - (idx + 1));
		set_env_value(all, ft_strdup(key), ft_strdup(value));
		free(key);
		free(value);
	}
	g_exit_code = 0;
}

static void	print_export(t_all *all)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->key);
		if (tmp->value)
		{
			printf("=\"%s\"\n", tmp->value);
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	ms_export(char **content, t_all *all)
{
	int	i;

	if (content[1] == NULL)
	{
		print_export(all);
		g_exit_code = 0;
		return ;
	}
	i = 1;
	while (content[i])
	{
		if (ft_isalpha(content[i][0]) || content[i][0] == '_')
		{
			set_env(content[i], all);
			g_exit_code = 0;
		}
		else
		{
			error_print("minishell: export: `", 1);
			error_print(content[i], 1);
			error_print("': not a valid identifier\n", 1);
		}
		i++;
	}
}
