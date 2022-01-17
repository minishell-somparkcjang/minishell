#ifndef TOKEN_H
# define TOKEN_H

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

/* tokenization */
t_token		*tokenization(char *s);

/* token_func */
void		token_init(t_token *token, char *str, t_token *next);
t_token		*token_free(t_token *token_head);
t_token		*token_malloc_init(char *str, t_type type, t_token *next);
void		token_insert(t_token *token, t_token *token_new);
t_token		*token_head_insert(t_token *token_head, t_token *token_new);

/* token_str */
char		*token_str(char *s, int *i);

/* token_type */
t_type		token_type(t_token *token_prev, t_token *token);

/* token_redirection */
int			token_redirection(t_token **token_head);

#endif
