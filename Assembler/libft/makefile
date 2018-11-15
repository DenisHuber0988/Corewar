# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jauplat <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 15:53:07 by jauplat           #+#    #+#              #
#    Updated: 2018/10/04 13:56:13 by dhuber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Wextra -Werror
OPTION = -c

FILE = ft_bzero.c get_next_line.c ft_realloc.c\
		ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c\
		ft_putstr.c ft_putstr_fd.c ft_putnbr.c ft_putnbr_fd.c\
		ft_strlen.c ft_swap.c \
		ft_memchr.c ft_memrchr.c \
		ft_strchr.c ft_strrchr.c \
		ft_strcmp.c ft_strncmp.c ft_strequ.c ft_strnequ.c \
		ft_strcat.c ft_strlcat.c ft_strncat.c ft_strjoin.c \
		ft_strnstr.c ft_strstr.c join_free.c njoin_free.c\
		ft_memcmp.c \
		ft_memset.c ft_memcpy.c ft_memmove.c ft_memccpy.c ft_memalloc.c ft_memdel.c \
		ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strsub.c ft_strtrim.c \
		ft_toupper.c ft_tolower.c \
		ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_isascii.c \
		ft_atoi.c ft_itoa.c ft_isnegative.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c \
		ft_strsplit.c ft_print_numbers.c ft_print_alphabet.c \
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c

OBJS = $(FILE:%.c=%.o)

.PHONY : all clean fclean re

all: $(OBJS) $(NAME)

%.o: %.c
	$(CC) $(FLAG) -o $@ -c $<

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJS)

fclean: 
	make clean
	rm -rf $(NAME)

re:
	make fclean
	make
