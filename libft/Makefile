# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/24 17:30:16 by cjang             #+#    #+#              #
#    Updated: 2021/12/03 13:48:30 by cjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =	ft_memset.c		ft_bzero.c		ft_memcpy.c		ft_memccpy.c	\
		ft_memmove.c	ft_memchr.c		ft_memcmp.c		ft_strlen.c		\
		ft_strlcpy.c	ft_strlcat.c	ft_strchr.c		ft_strrchr.c	\
		ft_strnstr.c	ft_strncmp.c	ft_atoi.c		ft_isalpha.c	\
		ft_isdigit.c	ft_isalnum.c	ft_isascii.c	ft_isprint.c	\
		ft_toupper.c	ft_tolower.c	ft_calloc.c		ft_strdup.c		\
																		\
		ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_split.c		\
		ft_itoa.c		ft_strmapi.c	ft_putchar_fd.c	ft_putstr_fd.c	\
		ft_putendl_fd.c	ft_putnbr_fd.c
SRCS_BONUS =	ft_lstnew.c		ft_lstadd_front.c		ft_lstsize.c	\
				ft_lstlast.c	ft_lstadd_back.c		ft_lstdelone.c	\
				ft_lstclear.c	ft_lstiter.c			ft_lstmap.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef BONUS_INCLUDE
	OBJS_FILE = $(OBJS) $(OBJS_BONUS)
else
	OBJS_FILE = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJS_FILE)
	ar rc $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

bonus:
	@make BONUS_INCLUDE=1 all

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
