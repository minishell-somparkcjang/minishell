/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sompark <sompark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:11:36 by sompark           #+#    #+#             */
/*   Updated: 2022/01/25 17:04:21 by sompark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* t_env에서 key값을 찾아 value를 반환 */
char	*find_env_key(t_all *all, char *key)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key))
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
		if (ft_strcmp(tmp2->key, key))
		{
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

void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	set_shlvl(t_all *all)
{
	char	*tmp;
	int		i;

	tmp = find_env_key(all, "SHLVL");
	i = (ft_atoi(tmp) + 1);
	set_env_value(all, strdup("SHLVL"), ft_itoa(i));
}
