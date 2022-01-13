#ifndef PARSE_H
# define PARSE_H

/* token_type 정의 */
typedef enum e_type
{
	nontype = 0,
	com,
	pip,
	r_in,
	r_out,
	r_outapp,
	r_here,
	fd_in,
	fd_out,
	r_file
}t_type;

/* readline에서 읽은 문자열을 파싱한 결과 */
typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}t_token;

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
	struct s_parse	*next;
}t_parse;

/* 제일 첫번째 명령이 있는 곳을 가리킴 */
typedef struct s_parse_all
{
	t_parse			*head;
}t_parse_all;

/* tokenization */
t_token		*tokenization(char *s);

/* parse_assemble */
t_parse		*parse_assemble(t_token *token_head);

/* token_func */
void		token_init(t_token *token, char *str, t_token *next);
void		token_free(t_token *token_head);
t_token		*token_malloc_init(char *str, t_type type);
void		token_insert(t_token *token, t_token *token_new);
t_token		*token_head_insert(t_token *token_head, t_token *token_new);

/* parse_func */
void		parse_free(t_parse *parse_head);

#endif
