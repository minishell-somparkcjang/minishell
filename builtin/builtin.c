#include "../include/minishell.h"

/* pwd */
static void	ms_pwd(t_all *all)
{
	char		*s;

	s = getcwd(NULL, 0);
	if (s != NULL)
		printf("%s\n", s);
	free(s);
	all->exit_code = 0;
}

/* env */
static void	ms_env(t_all *all)
{
	t_env	*tmp;

	tmp = all->env->head;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	all->exit_code = 0;
}

/* unset */
static void	ms_unset(char **split_str, t_all *all)
{
	if (split_str[1] == 0)
		return ;
	delete_env_key(all, split_str[1]);
}

/* exit */
static void	ms_exit(void)
{
	exit(0);
}

/* 이부분은 외부함수 사용 시에 필요없을 듯 */
static void	ms_command_not_found(char **split_str)
{
	printf("minishell: %s: command not found\n", split_str[0]);
}

/* 임시로 split한 것 */
static void	free_split_str(char **split_str)
{
	int			i;

	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
}

/* minishell 내장함수 분기점*/
void	ms_builtin(char *str, t_all *all)
{
	char	**split_str;
	// int		check;

	split_str = ft_split(str, ' ');
	// 대문자도 체크해야함.
	if (!split_str[0])
		return ;
	if (ft_strncmp(split_str[0], "echo", ft_strlen_long(split_str[0], "echo")) == 0)
		ms_echo(split_str, all);
	else if (ft_strncmp(split_str[0], "cd", ft_strlen_long(split_str[0], "cd")) == 0)
		ms_cd(split_str, all);
	else if (ft_strncmp(split_str[0], "pwd", ft_strlen_long(split_str[0], "pwd")) == 0)
		ms_pwd(all);
	else if (ft_strncmp(split_str[0], "export", ft_strlen_long(split_str[0], "export")) == 0)
		ms_export(split_str, all);
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
