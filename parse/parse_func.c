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
		}
		parse_prev = parse;
		parse = parse->next;
		free(parse_prev);
	}
	parse_head = NULL;
}