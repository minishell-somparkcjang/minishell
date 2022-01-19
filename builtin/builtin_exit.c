#include "../include/minishell.h"

void	ms_exit(char **content, t_all *all)
{
	int	valid;
	int	i;

	valid = 1;
	if (content[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	} //exit 123 123
	i = 0;
	if (content[2] == NULL)
	{
		while (content[1][i])
		{
			if (!ft_isdigit(content[1][i]))
			{
				valid = 0;
				break;
			}
			i++;
		}
		if (valid)
		{
			printf("exit\n");
			exit(ft_atoi(content[1]));
		}
		else
		{
			printf("exit\nminishell: exit %s: numeric argument required\n", content[1]);
			exit(255);
		}
	}
	else
	{
		g_exit_code = 1;
		printf("exit\nminishell: exit: too many arguments\n");
		return ;
	}
}