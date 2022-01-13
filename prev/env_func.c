/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:06:54 by cjang             #+#    #+#             */
/*   Updated: 2022/01/06 13:17:23 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
