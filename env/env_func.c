/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:32 by sompark           #+#    #+#             */
/*   Updated: 2022/01/24 18:24:39 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*make_newenv(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		error_exit("Malloc Failure\n", 1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

/* t_env에서 key-value값 추가(기존에 key값이 있으면 덮어쓰기) */
void	set_env_value(t_all *all, char *key, char *newvalue)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			free(key);
			tmp->value = newvalue;
			return ;
		}
		if (tmp->next == NULL)
		{	
			tmp->next = make_newenv(key, newvalue);
			printf("key:%s value: %s\n", tmp->next->key, tmp->next->value);
			all->env->num_env++;
			return ;
		}
		tmp = tmp->next;
	}
}

static char	*make_env(t_env *tmp)
{
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_str;

	tmp_key = ft_strdup(tmp->key);
	if (tmp->value)
		tmp_value = ft_strdup(tmp->value);
	else
		tmp_value = ft_strdup("");
	tmp_str = ft_strjoin(tmp_key, "=");
	free(tmp_key);
	tmp_key = ft_strjoin(tmp_str, tmp_value);
	free(tmp_str);
	free(tmp_value);
	return (tmp_key);
}

char	**ret_env(t_all *all)
{
	char	**env;
	int		i;
	t_env	*tmp;

	env = malloc(sizeof(char *) * (all->env->num_env + 1));
	if (env == NULL)
		error_exit("Malloc Failure\n", 1);
	i = 0;
	tmp = all->env->head;
	while (tmp)
	{
		env[i++] = make_env(tmp);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
