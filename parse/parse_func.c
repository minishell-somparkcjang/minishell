#include "../include/minishell.h"

void	parse_free(t_parse *parse_head)
{
	t_parse			*parse;
	t_parse			*parse_prev;
	t_redirection	*red;
	t_redirection	*red_prev;
	t_command		*com;
	int				i;

	parse = parse_head;
	while (parse != NULL)
	{
		red = parse->left;
		while (red != NULL)
		{
			if (red->file_name != NULL)
				free(red->file_name);
			red_prev = red;
			red = red->next;
			free(red_prev);
		}
		com = parse->right;
		// com->comaand = con->content[i]이기 때문에 free 할 필요 x
		// 	free(com->command);
		i = 0;
		if (com != NULL)
		{
			while (com->content[i] != NULL)
			{
				free(com->content[i]);
				i++;
			}
			free(com->content);
			free(com);
		}
		parse_prev = parse;
		parse = parse->next;
		free(parse_prev);
	}
	parse_head = NULL;
}

int	parse_size(t_parse *parse_head)
{
	int		len;
	t_parse	*parse;

	len = 0;
	parse = parse_head;
	while (parse)
	{
		len++;
		parse = parse->next;
	}
	return (len);
}
