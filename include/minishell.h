#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parse.h"
# include "redirection.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_env_lst
{
	t_env			*head;
	int				num_env;
}t_env_lst;

typedef struct s_all
{
	t_env_lst		*env;
	t_parse			*parser;
	int				exit_code;
}t_all;

/* init_env */
void	init_env(t_all *all, char **env);

/* env_func */
char	*find_env_key(t_all *all, char *key);
void	delete_env_key(t_all *all, char *key);
void	set_env_value(t_all *all, char *key, char *newvalue);

/* utils */
size_t	ft_strlen_long(const char *s1, const char *s2);
int		ft_is_fd_range(char *s, int s_len);

/* builtin */
void		ms_builtin(char *str, t_all *all);
void		ms_cd(char **content, t_all *all);
void		ms_echo(char **content, t_all *all);
void		ms_export(char **content, t_all *all);

/* parse */
void		parse_main(char *s, t_all *all);

/* token_env */
void		token_env(t_token *token, t_all *all);

#endif

