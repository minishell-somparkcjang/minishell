#include "../include/minishell.h"

/* t_env에서 key값을 찾아 value를 반환 */
char	*find_env_key(t_all *all, char *key)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen_long(tmp->key, key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/* t_env에서 key값을 찾아 t_env값 삭제 */
void	delete_env_key(t_all *all, char *key)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp1 = NULL;
	tmp2 = all->env->head;
	while (tmp2)
	{
		if (ft_strncmp(tmp2->key, key, ft_strlen_long(tmp2->key, key)) == 0)
		{
			if (tmp1 == NULL)
				all->env->head = tmp2->next;
			else
				tmp1->next = tmp2->next;
			free(tmp2);
			all->env->num_env--;
			return ;
		}
		tmp1 = tmp2;
		tmp2 = tmp2->next;
	}
}

/* t_env에서 key-value값 추가(기존에 key값이 있으면 덮어쓰기) */
void	set_env_value(t_all *all, char *key, char *newvalue)
{
	t_env	*tmp;
	t_env	*new;

	tmp = all->env->head;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen_long(tmp->key, key)) == 0)
		{
			free(tmp->value);
			free(key);
			tmp->value = newvalue;
			return ;
		}
		if (tmp->next == NULL)
		{
			new = malloc(sizeof(t_env));
			if (!new)
			{
				//malloc실패
			}
			new->key = key;
			new->value = newvalue;
			new->next = NULL;
			tmp->next = new;
			all->env->num_env++;
			return ;
		}
		tmp = tmp->next;
	}
}

// env 연결리스트 -> "key=value" 2차원배열로 return
char	**ret_env(t_all *all)
{
	char	**env;
	int		i;
	char	*tmp_key;
	char	*tmp_value;
	t_env	*tmp;

	env = malloc(sizeof(char *) * all->env->num_env);
	if (env == NULL)
	{
		//malloc실패
	}
	i = 0;
	tmp = all->env->head;
	while (tmp)
	{
		tmp_key = ft_strdup(tmp->key);
		tmp_value = ft_strdup(tmp->value);
		env[i] = ft_strjoin(tmp_key, "=");
		free(tmp_key);
		tmp_key = ft_strjoin(env[i], tmp_value);
		free(env[i]);
		free(tmp_value);
		env[i++] = tmp_key;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
