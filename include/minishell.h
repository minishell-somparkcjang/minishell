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
	int				pip_cnt;
}t_all;

/* init_env */
void		init_env(t_all *all, char **env);

/* env_func */
char		*find_env_key(t_all *all, char *key);
void		delete_env_key(t_all *all, char *key);
void		set_env_value(t_all *all, char *key, char *newvalue);
char		**ret_env(t_all *all);

/* utils */
size_t		ft_strlen_long(const char *s1, const char *s2);
int			ft_is_fd_range(char *s, int s_len);
int			ft_strcmp(char *str1, char *str2);

/* builtin */
void		exec_builtin(t_command *str, t_all *all);
void		ms_cd(char **content, t_all *all);
void		ms_echo(char **content, t_all *all);
void		ms_export(char **content, t_all *all);
void		ms_unset(char **content, t_all *all);
void		ms_exit(char **content, t_all *all);
int			is_builtin(t_command *str, t_all *all);

/* parse */
void		parse_main(char *s, t_all *all);

/* parse_assemble */
t_parse		*parse_assemble(t_token *token_head, t_all *all);

/* token_env */
void		token_env(t_token *token, t_all *all);

/* exec */
void		start_ms(t_all *all);

/* exec_sys */
void		exec_cmd(t_command *command, t_all *all, char **envp);
#endif
