#include "../include/minishell.h"

static int	is_equal(char *content)
{
	int	i;

	while (content[i])
	{
		if (content[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	set_env(char *content)
{
	int	idx;

	idx = is_equal(content);
	if (idx == -1)
	{
		
	}
	else
	{

	}
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
			printf("=\"%s\"", tmp->value);
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
		all->exit_code = 0;
		return ;
	}
	i = 1;
	while (content[i])
	{
		if (ft_isalpha(content[i][0]) || content[i][0] == '_')
		{
			set_env(content[i]);
			all->exit_code = 0;
		}
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", content[i]);
			all->exit_code = 1;
		}
		i++;
	}
}