# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhuber <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/26 17:32:36 by dhuber            #+#    #+#              #
#    Updated: 2018/06/29 16:34:42 by dhuber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = @clang

CFLAGS = -Wall -Wextra -Werror -g

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	  ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	  ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	  ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	  ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	  ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
	  ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	  ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
	  ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
	  ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	  ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	  ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strrev.c ft_print_bit.c \
	  ft_swap.c ft_is_lower.c ft_is_upper.c ft_is_space.c get_next_line.c \
	  ft_itoa_base.c ft_putwchar.c ft_putwchar_fd.c ft_nblen.c \
	  ft_putlnbr_base.c ft_utoa_base.c ft_wlen.c ft_putwstr.c ft_max.c \
	  ft_power.c ft_atoll.c my_isdigit.c 

.PHONY: all clean fclean re

INCLUDE = libft.h \
		  get_next_line.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compilation libft !"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME) 

$(OBJ): libft.h \
	get_next_line.h

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
