#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parse.h"
# include "redirection.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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

int	g_exit_code;

/* init_env */
void	init_env(t_all *all, char **env);

/* env_func */
char	*find_env_key(t_all *all, char *key);
void	delete_env_key(t_all *all, char *key);
void	set_env_value(t_all *all, char *key, char *newvalue);
char	**ret_env(t_all *all);
void	free_env(char **envp);
void	set_shlvl(t_all *all);

/* utils */
size_t	ft_strlen_long(const char *s1, const char *s2);
int		ft_is_fd_range(char *s, int s_len);
int		ft_strcmp(char *str1, char *str2);
t_parse	*ret_parse_prev(t_all *all, t_parse *parse);
int		ft_isspace(char *str);
void	free_env(char **envp);

/* builtin */
void	exec_builtin(t_command *str, t_all *all);
void	ms_cd(char **content, t_all *all);
void	ms_echo(char **content);
void	ms_export(char **content, t_all *all);
void	ms_unset(char **content, t_all *all);
void	ms_exit(char **content);
int		is_builtin(t_command *str);

/* parse */
void	parse_main(char *s, t_all *all);
t_token	*tokenization(t_all *all, char *s);

/* parse_assemble */
t_parse	*parse_assemble(t_token *token_head, t_all *all);

/* token_special */
int		token_special(t_token *token, t_all *all);
char	*env_get(char *str, int *i, t_all *all);

/* token_quote */
char	*double_quote(char *str, int *i, t_all *all);
/* exec */
void	start_ms(t_all *all);
void	exec_single_cmd(t_command *command, t_all *all, char **envp);
void	exec_cmd(t_command *command, t_all *all, char **envp);
void	set_exit(int status);

/* signal */
void	signal_handle(void);
void	heredoc_sigint(int signo);
void	handle_signal(int signo);

/* error */
int		error_print(char *str, int exit_code);
int		error_print3(char *str1, char *str2, char *str3, int exit_code);
void	error_exit(char *str, int exit_code);
void	error_handler(char *arg, int _errno);

/* error_handler2 */
int		error_print_endl(char *str, int exit_code);
void	*error_print_null(char *str, int exit_code);
#endif
