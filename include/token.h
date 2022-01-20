/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:44:41 by cjang             #+#    #+#             */
/*   Updated: 2022/01/20 18:33:52 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
char		*token_str_return(char *s, int i_start, int i_end);

/* token_init */
void		token_init(t_token *token, char *str, t_token *next);
t_token		*token_malloc_init(char *str, t_type type);

/* token_func */
t_token		*token_free(t_token *token_head);
void		token_insert(t_token *token, t_token *token_new);
t_token		*token_head_insert(t_token *token_head, t_token *token_new);

/* token_str */
char		*token_str(char *s, int *i);

/* token_type */
t_type		token_type(t_token *token_prev, t_token *token);

/* token_redirection */
int			token_redirection(t_token **token_head);

/* token_redirection2 */
int			token_redi_insert(\
			t_token **t_h, t_token **t, t_token **t_p, char **s);

/* token_quote */
char		*single_quote(char *str, int *i);

/* utils */
char		*ft_strdup_error_check(char *str);
int			quotes_flag_check(char c, int quotes_flag);
void		*error_print_null(char *str, int exit_code);

/* parse_func */
int			token_com_len(t_token *token);
int			token_red_len(t_token *token);
#endif
