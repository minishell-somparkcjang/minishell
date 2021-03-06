/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:39 by sompark           #+#    #+#             */
/*   Updated: 2022/01/25 16:29:53 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 환경변수 linked list로 세팅 */
static void	set_env(char *key, char *value, t_all *all)
{
	t_env	*env_node;
	t_env	*tmp;

	env_node = malloc(sizeof(t_env));
	if (env_node == NULL)
		error_exit("Malloc Failure\n", 1);
	env_node->key = key;
	env_node->value = value;
	env_node->next = NULL;
	if (all->env->num_env == 0)
	{
		all->env->head = env_node;
	}
	else
	{
		tmp = all->env->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env_node;
	}
	all->env->num_env++;
}

/* envp에서 가져올 환경변수 key or value의 len 리턴 */
static int	get_equl_idx(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	return (i);
}

/* envp에서 환경변수의 value값 리턴 */
static char	*get_env_value(char *env, int len)
{
	int		start;
	char	*ret;

	start = get_equl_idx(env) + 1;
	ret = ft_substr(env, start, len - start);
	return (ret);
}

/* envp에서 환경변수의 key값 리턴 */
static char	*get_env_key(char *env)
{
	int		len;
	char	*ret;

	len = get_equl_idx(env);
	ret = ft_substr(env, 0, len);
	return (ret);
}

/* envp에 있는 환경변수들을 linked list화 */
void	init_env(t_all *all, char **env)
{
	int		i;
	int		len;
	char	*key;
	char	*value;

	i = 0;
	all->env = malloc(sizeof(t_env_lst));
	if (all->env == NULL)
		error_exit("Malloc Failure\n", 1);
	all->env->num_env = 0;
	all->env->head = NULL;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		key = get_env_key(env[i]);
		value = get_env_value(env[i], len);
		if (value == NULL)
			value = "";
		set_env(key, value, all);
		i++;
	}
	all->pip_cnt = 0;
	all->parser = NULL;
	set_shlvl(all);
}
