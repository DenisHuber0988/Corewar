#
#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhuber <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/12 16:39:57 by dhuber            #+#    #+#              #
#    Updated: 2018/10/16 14:56:24 by dhuber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

CC = @clang

CFLAGS = -Wall -Wextra -Werror -g3 -I ./$(INCLUDES_PATH)

SOURCES_PATH = src

SOURCES_NAME = ft_printf.c \
		   ft_printf_tab.c \
		   ft_printf_field.c \
		   ft_flag_b.c \
		   ft_flag_c.c \
		   ft_flag_d.c \
		   ft_flag_f.c \
		   ft_flag_o.c \
		   ft_flag_p.c \
		   ft_flag_s.c \
		   ft_flag_u.c \
		   ft_flag_x.c \
		   ft_noflag.c \
		   ft_wrong.c \
		   ft_flag_capx.c \
		   ft_handle_zero.c \
		   ft_handle_neg.c \
		   ft_handle_pos.c \
		   ft_handle_hex.c \
		   ft_handle_bin.c \
		   ft_handle_ptr.c \
		   ft_handle_str.c \
		   ft_handle_wstr.c \
		   ft_handle_char.c \
		   ft_handle_wchar.c \
		   ft_printf_flag.c \

SOURCES = $(addprefix $(SOURCES_PATH)/,$(SOURCES_NAME))

OBJECTS_PATH = obj
OBJECTS_NAME = $(SOURCES_NAME:.c=.o)
OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(OBJECTS_NAME))

INCLUDES_PATH = includes
INCLUDES_NAME = ft_printf.h
INCLUDES = $(addprefix $(INCLUDES_PATH)/,$(INCLUDES_NAME))

LIB = ./libft_first/libft_first.a

NAME = libft.a

all: $(NAME)

$(NAME): libftcreate $(OBJECTS) $(LIB)
	@libtool -static -o $(NAME) $(LIB) $(OBJECTS)
	@echo "Compilation libft.a !"

libftcreate:
	@make all -C ./libft_first/

$(OBJECTS): $(SOURCES) $(INCLUDES)
	@mkdir $(OBJECTS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@mv $(OBJECTS_NAME) $(OBJECTS_PATH)

clean:
	@make clean -C ./libft_first/
	@rm -f $(OBJECTS)
	@rmdir $(OBJECTS_PATH) 2> /dev/null || true
	@echo "\033[32;2m Cleaned libft.a\033[0m"

fclean: clean
	@make fclean -C ./libft_first/
	@rm -f $(NAME)
	@echo "\033[32;2m Fcleaned libft.a\033[0m"

re: fclean all

norme:
	norminette $(SOURCES)
