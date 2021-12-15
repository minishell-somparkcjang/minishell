# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 13:33:25 by cjang             #+#    #+#              #
#    Updated: 2021/12/15 17:14:30 by cjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = # -Wall -Wextra -Werror
READLINE = -lreadline

LIBFT = libft
LIBFT_A = libft/libft.a

SRCS_DIR = ./
SRCS_FILE = main_tmp.c\
			parse.c\
			init_env.c\


SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS = $(SRCS:.c=.o)
NAME_MINISHELL = minishell

all: $(LIBFT) $(NAME_MINISHELL)

$(LIBFT):
	@make -C $(LIBFT)

$(NAME_MINISHELL): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS)  $(LIBFT_A) $(OBJS) -o $(NAME_MINISHELL) $(READLINE)

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
