# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jauplat <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 14:04:17 by jauplat           #+#    #+#              #
#    Updated: 2018/07/19 15:17:08 by jauplat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
FLAG = -Wall -Wextra -Werror -g3 -fsanitize=address
OPTION = -o
LIBFT = ./libft/libft.a

FILE = src/main.c src/error.c src/init.c src/get_file.c src/name.c src/comment.c src/instruction.c src/prog.c src/op.c src/utils.c src/util2.c src/argument.c src/moove.c src/tmp.c src/label_chars.c\


OBJ = $(FILE:src/%.c=src/%.o)

.PHONY: all clean fclean re

all: $(OBJ) $(NAME)

$(OBJ): src/%.o: src/%.c
	gcc $(FLAG) $(OPTION) $@ -c $<

$(NAME): $(OBJ)
	cd libft && make && cd ..
	gcc $(FLAG) $(OPTION) $(NAME) $(LIBFT) $(OBJ)

clean:
	cd libft && make clean && cd ..
	rm -rf $(OBJ)

fclean:
	make clean
	cd libft && make fclean && cd ..
	rm -rf $(NAME)

re:
	make fclean
	make all
