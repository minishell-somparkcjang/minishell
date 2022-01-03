# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 13:33:25 by cjang             #+#    #+#              #
#    Updated: 2022/01/02 13:13:54 by cjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = # -Wall -Wextra -Werror
READLINE = -lreadline

LIBFT = libft
LIBFT_A = libft/libft.a

SRCS_DIR = ./
SRCS_FILE = main.c\
			parse.c\
			init_env.c\
			token_func.c\
			tokenization.c\
			token_env.c\
			utils.c\


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
