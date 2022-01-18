#include "../include/minishell.h"

static void	delete_env(t_all *all, char *key)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp1 = NULL;
	tmp2 = all->env->head;
	while (tmp2)
	{
		if (ft_strncmp(tmp2->key, key, ft_strlen_long(tmp2->key, key)) == 0)
		{
			// printf("delete key: %s, value %s\n", tmp2->key, tmp2->value);
			if (tmp1 == NULL)
				all->env->head = tmp2->next;
			else
				tmp1->next = tmp2->next;
			free(tmp2->key);
			free(tmp2->value);
			free(tmp2);
			all->env->num_env--;
			return ;
		}
		tmp1 = tmp2;
		tmp2 = tmp2->next;
	}
}

void	ms_unset(char **content, t_all *all)
{
	int	i;

	if (content[1] == NULL)
	{
		all->exit_code = 0;
		return ;
	}
	i = 1;
	while (content[i])
	{
		if (ft_isalpha(content[i][0]) || content[i][0] == '_')
		{
			// printf("test unset: key >> %s <<", content[i]);
			delete_env(all, content[i]);
			all->exit_code = 0;
		}
		else
		{
			printf("minishell: unset: `%s': not a valid identifier\n", content[i]);
			all->exit_code = 1;
		}
		i++;
	}
}