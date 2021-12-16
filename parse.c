/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:12 by cjang             #+#    #+#             */
/*   Updated: 2021/12/16 16:08:31 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 문자열 두개 중 가장 긴 값의 문자열 길이를 반환
static size_t	ft_strlen_long(const char *s1, const char *s2)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (s1[i1] != '\0')
		i1++;
	while (s2[i2] != '\0')
		i2++;
	if (i1 > i2)
		return (i1);
	else
		return (i2);
}

// t_env에서 key값을 찾아 value를 반환
static char	*find_env_key(t_all *all, char *key)
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

// t_env에서 key값을 찾아 t_env값 삭제
static void	delete_env_key(t_all *all, char *key)
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

static void	ms_echo(char **split_str)
{
	int		i;

	i = 1;
	while (split_str[i])
	{
		printf("%s", split_str[i++]);
		if (split_str[i])
			printf(" ");
	}
	printf("\n");
}

static void	ms_pwd(t_all *all)
{
	char		*s;

	s = find_env_key(all, "PWD");
	if (s != NULL)
		printf("%s\n", s);
}

static void	ms_env(t_all *all)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	ms_unset(char **split_str, t_all *all)
{
	if (split_str[1] == 0)
		return ;
	delete_env_key(all, split_str[1]);
}

static void	ms_exit(void)
{
	exit(0);
}

static void	ms_command_not_found(char **split_str)
{
	printf("minishell: %s: command not found\n", split_str[0]);
}

static void	free_split_str(char **split_str)
{
	int			i;

	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
}

void	parse(char *str, t_all *all)
{
	char	**split_str;
	// int		check;

	split_str = ft_split(str, ' ');
	// 대문자도 체크해야함.
	if (!split_str[0])
		return ;
	if (ft_strncmp(split_str[0], "echo", ft_strlen_long(split_str[0], "echo")) == 0)
		ms_echo(split_str);
	else if (ft_strncmp(split_str[0], "cd", ft_strlen_long(split_str[0], "cd")) == 0)
		;
	else if (ft_strncmp(split_str[0], "pwd", ft_strlen_long(split_str[0], "pwd")) == 0)
		ms_pwd(all);
	else if (ft_strncmp(split_str[0], "export", ft_strlen_long(split_str[0], "export")) == 0)
		;
	else if (ft_strncmp(split_str[0], "unset", ft_strlen_long(split_str[0], "unset")) == 0)
		ms_unset(split_str, all);
	else if (ft_strncmp(split_str[0], "env", ft_strlen_long(split_str[0], "env")) == 0)
		ms_env(all);
	else if (ft_strncmp(split_str[0], "exit", ft_strlen_long(split_str[0], "exit")) == 0)
		ms_exit();
	else
		ms_command_not_found(split_str);
	free_split_str(split_str);
}
	// argv로 들어오는게 아니라서 띄어쓰기, '' "" 각각에 대해 대응을 해야 함.
	// 일단 split으로 나눠보기
