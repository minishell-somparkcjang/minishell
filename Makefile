CC = gcc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline -L ${HOME}/.brew/opt/readline/lib -I ${HOME}/.brew/opt/readline/include
READLINE_INCLUDE = -I ${HOME}/.brew/opt/readline/include
LIBFT = libft
LIBFT_A = libft/libft.a

SRCS_DIR = ./
SRCS_FILE = main.c\
			parse/parse_assemble.c\
			parse/parse_func.c\
			parse/parse_init.c\
			parse/parse.c\
			parse/token_env.c\
			parse/token_func.c\
			parse/token_init.c\
			parse/token_quote.c\
			parse/token_redirection.c\
			parse/token_redirection2.c\
			parse/token_special.c\
			parse/token_str.c\
			parse/token_type.c\
			parse/tokenization.c\
			parse//utils.c\
			env/init_env.c\
			env/env_func.c\
			env/env_func2.c\
			redirection/redirection.c\
			redirection/heredoc.c\
			redirection/std_backup.c\
			pipe/pipe.c\
			builtin/builtin.c\
			builtin/builtin_cd.c\
			builtin/builtin_echo.c\
			builtin/builtin_export.c\
			builtin/builtin_unset.c\
			builtin/builtin_exit.c\
			execution/start_ms.c\
			execution/exec_cmd.c\
			error_handler/error_handler.c\
			error_handler/error_handler2.c\
			utils.c\
			signal.c\


SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS = $(SRCS:.c=.o)
NAME_MINISHELL = minishell

all: $(LIBFT) $(NAME_MINISHELL)

$(LIBFT):
	make -C $(LIBFT)

$(NAME_MINISHELL): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME_MINISHELL) $(READLINE)

%.o: %.c
	$(CC) -c  $(CFLAGS) $(READLINE_INCLUDE) -o  $@ $<

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME_MINISHELL)

re: fclean all

.PHONY: all bonus clean fclean re $(LIBFT) $(LIBFT_A)
