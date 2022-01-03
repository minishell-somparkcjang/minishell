#include "minishell.h"

void	print_env(t_all *all)
{
	t_env	*tmp;

	tmp = all->env->head;
	printf("env_num: %d\n", all->env->num_env);
	while (tmp)
	{
		printf("key:%s, value:%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	set_env(char *key, char *value, t_all *all)
{
	t_env	*env_node;
	t_env	*tmp;

	env_node = malloc(sizeof(t_env));
	// error처리
	if (env_node == NULL)
		return ;
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
		{
			tmp = tmp->next;
		}
		tmp->next = env_node;
	}
	all->env->num_env++;
}

int	get_equl_idx(char *env)
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

char	*get_env_value(char *env, int len)
{
	int		start;
	char	*ret;

	start = get_equl_idx(env) + 1;
	ret = ft_substr(env, start, len - start);
	return (ret);
}

char	*get_env_key(char *env)
{
	int		len;
	char	*ret;

	len = get_equl_idx(env);
	ret = ft_substr(env, 0, len);
	return (ret);
}

void	init_env(t_all *all, char **env)
{
	int		i;
	int		len;
	char	*key;
	char	*value;

	i = 0;
	all->env = malloc(sizeof(t_env_lst));
	//error처리
	if (all->env == NULL)
		return ;
	all->env->num_env = 0;
	all->env->head = NULL;
	while (env[i])
	{
		// printf("%s\n", env[i]);
		len = ft_strlen(env[i]);
		key = get_env_key(env[i]);
		value = get_env_value(env[i], len);
		// printf("%d	%s	%s\n", len, key, value);
		if (value == NULL)
			value = "";
		set_env(key, value, all);
		i++;
	}
	// print_env(all);
}
