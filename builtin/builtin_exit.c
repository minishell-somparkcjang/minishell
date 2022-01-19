#include "../include/minishell.h"

void	ms_exit(char **content)
{
	int	valid;
	int	i;

	valid = 1;
	if (content[1] == NULL)
	{
		ft_putendl_fd("exit\n", 1);
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
			ft_putendl_fd("exit\n", 1);
			exit(ft_atoi(content[1]));
		}
		else
		{
			error_print("exit\nminishell: exit ", 255);
			error_print(content[1], 255);
			error_exit(": numeric argument required\n", 255);
		}
	}
	else
	{
		error_print("exit\nminishell: exit: too many arguments\n", 1);
		return ;
	}
}