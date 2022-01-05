/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:25:12 by cjang             #+#    #+#             */
/*   Updated: 2022/01/05 18:00:19 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

void	parse_main(char *s, t_all *all)
{
	t_token		*token_header;

	// 따옴표 짝에 대한 체크를 따로 할지, 아니면 구조체를 형성하는 과정에서 할지 고민요소
	token_header = tokenization(s);
	token_env(token_header, all);
}
