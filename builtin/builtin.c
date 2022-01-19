#include "../include/minishell.h"

/* pwd */
static void	ms_pwd(void)
{
	char		*s;

	s = getcwd(NULL, 0);
	if (s != NULL)
		printf("%s\n", s);
	free(s);
	g_exit_code = 0;
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
	g_exit_code = 0;
}

//str = parser->right
void	exec_builtin(t_command *str, t_all *all)
{
	char *command;
	char **content;

	command = str->command;
	content = str->content;
	if (ft_strcmp(command, "echo") || ft_strcmp(command, "ECHO"))
		ms_echo(content);
	else if (ft_strcmp(command, "cd"))
		ms_cd(content, all);
	else if (ft_strcmp(command, "pwd") || ft_strcmp(command, "PWD"))
		ms_pwd();
	else if (ft_strcmp(command, "export"))
		ms_export(content, all);
	else if (ft_strcmp(command, "unset"))
		ms_unset(content, all);
	else if (ft_strcmp(command, "env") || ft_strcmp(command, "ENV"))
		ms_env(all);
	else if (ft_strcmp(command, "exit"))
		ms_exit(content);
}

//str = parser->right
int is_builtin(t_command *str)
{
	char *command;

	command = str->command;
	if (ft_strcmp(command, "echo") || ft_strcmp(command, "ECHO")
		|| ft_strcmp(command, "cd") || ft_strcmp(command, "pwd")
		|| ft_strcmp(command, "PWD") || ft_strcmp(command, "export")
		|| ft_strcmp(command, "unset") || ft_strcmp(command, "env")
		|| ft_strcmp(command, "ENV") || ft_strcmp(command, "exit"))
		return (1);
	return (0);
}