CC = gcc
CFLAGS = # -Wall -Wextra -Werror
READLINE = -lreadline

LIBFT = libft
LIBFT_A = libft/libft.a

SRCS_DIR = ./
SRCS_FILE = main.c\
			parse/token_func.c\
			parse/token_env.c\
			parse/parse_assemble.c\
			parse/tokenization.c\
			parse/parse.c\
			parse/parse_func.c\
			env/init_env.c\
			env/env_func.c\
			redirection/redirection.c\
			redirection/std_backup.c\
			utils.c\
			builtin/builtin_echo.c\
			builtin/builtin_export.c\
			# builtin/builtin.c\
			# builtin/builtin_cd.c\

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS = $(SRCS:.c=.o)
NAME_MINISHELL = minishell

all: $(LIBFT) $(NAME_MINISHELL)

$(LIBFT):
	@make -C $(LIBFT)

$(NAME_MINISHELL): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME_MINISHELL) $(READLINE)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME_MINISHELL)

re: fclean all

.PHONY: all bonus clean fclean re $(LIBFT)
