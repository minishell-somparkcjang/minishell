#ifndef PARSE_H
# define PARSE_H

# include "token.h"

/* 리다이렉션의 input_fd, 리다이렉션 타입, output_fd OR filename */
typedef struct s_redirection
{
	int						fd_left;
	t_type					type;
	int						fd_right;
	char					*file_name;
	struct s_redirection	*next;
}t_redirection;

/* 명령어와 인자들 */
typedef struct s_command
{
	char			*command;
	char			**content;
}t_command;

/* 파이프 단위로 linked_list */
/* 우선순위가 [리다이렉션] > [명령] 이기때문에, left->right 순으로 순회 */
typedef struct s_parse
{
	t_redirection	*left;
	t_command		*right;
	int				pipe_fd[2];
	struct s_parse	*next;
}t_parse;

/* 제일 첫번째 명령이 있는 곳을 가리킴 */
typedef struct s_parse_all
{
	t_parse			*head;
}t_parse_all;

/* parse_func */
void			parse_free(t_parse *parse_head);
int				parse_size(t_parse *parse_head);

/* redirection */
int				red_apply(t_redirection *red_head);
int				heredoc_apply(t_parse *parse_head);

/* pipe */
int				pipe_fd_connect(t_parse *parse_prev, t_parse *parse);
int				pipe_fd_close(t_parse *parse_prev, t_parse *parse);

/* parse_func */
void			*red_free(t_redirection *red);

/* parse_init */
t_command		*com_malloc_init(t_token *token);
t_redirection	*red_malloc_init(t_token *token);
t_parse			*parse_malloc_init(t_redirection *r, t_command *c, t_parse *p);

/* parse */
void			print_parse(t_parse *parse);
#endif
