.PHONY: all, clean, fclean, re, norm

#---------------------------------------------------------#
# 				COMPILER, FLAGS AND LIBRARY				  #
#---------------------------------------------------------#
CC = clang
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
CFVM = -Weverything

ASM_LIB_PATH = Assembler/libft
ASM_LIB = Assembler/libft/libft.a
VM_LIB_PATH = VM/libft
VM_LIB = VM/libft/libft.a

#---------------------------------------------------------#
# NAME, PATHS, SOURCES, OBJECTSS AND INCLUDES FOR THE ASM #
#---------------------------------------------------------#
ASM_NAME = asm

ASM_SRCS_PATH = Assembler/asm_sources
ASM_SRCS_NAME = main.c \
				argument.c error.c init.c label_chars.c moove.c op.c tmp.c \
				utils.c comment.c get_file.c instruction.c name.c prog.c util2.c
ASM_SRCS = $(addprefix $(ASM_SRCS_PATH)/,$(ASM_SRCS_NAME))

ASM_OBJS_PATH = Assembler/asm_objects
ASM_OBJS_NAME = $(ASM_SRCS_NAME:%.c=%.o)
ASM_OBJS = $(addprefix $(ASM_OBJS_PATH)/,$(ASM_OBJS_NAME))

ASM_INC = Assembler/asm_includes/asm.h Assembler/asm_includes/op.h

#-----------------------------------------------------------#
#	NAME, PATHS, SOURCES, OBJECTSS AND INCLUDES FOR THE VM	#
#-----------------------------------------------------------#
VM_NAME = corewar

VM_SRCS_PATH = VM/vm_sources
VM_SRCS_NAME = main.c \
				ft_error.c parse_flag.c parse_champ.c init_vm.c my_function.c \
				ft_check_address.c ft_place_champ.c ft_place_four_champs.c \
				load_arena.c instruction.c recup_arg.c \
				op.c op_aff.c op_fork.c op_ldi.c op_live.c op_lldi.c op_or.c \
				op_sti.c op_xor.c op_add.c op_and.c op_ld.c op_lfork.c \
				op_lld.c op_st.c op_zjmp.c op_sub.c \
				run_vm.c  ft_vm_move.c handle_fork.c dump.c print_tools.c \
				parse_flag2.c

VM_SRCS = $(addprefix $(VM_SRCS_PATH)/,$(VM_SRCS_NAME))

VM_OBJS_PATH = VM/vm_objects
VM_OBJS_NAME = $(VM_SRCS_NAME:.c=.o)
VM_OBJS = $(addprefix $(VM_OBJS_PATH)/,$(VM_OBJS_NAME))

VM_INC = VM/vm_includes/virtual_machine.h VM/vm_includes/op.h VM/vm_includes/printer.h

NAME = Create_exec

all: libftcreate $(NAME)

libftcreate:
	@echo "\033[31;5;mCompiling ASM_lib...\033[0m"
	@make all -C $(ASM_LIB_PATH)
	@echo "\033[31;5;mCompiling VM_lib...\033[0m"
	@make all -C $(VM_LIB_PATH)
	@echo "\033[31;3mCompiling ASM_lib and VM_lib Done !\033[0m"

$(NAME): $(ASM_NAME) $(VM_NAME)

$(ASM_NAME): libftcreate $(ASM_LIB) $(ASM_OBJS)
	@$(CC) -o $(ASM_NAME) $(CFLAGS) $(ASM_LIB) $(ASM_OBJS)
	@echo "\n\033[1;4mASM CREATED.\033[0m"

$(ASM_OBJS): $(ASM_SRCS) $(ASM_INC)
	@mkdir $(ASM_OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $(ASM_SRCS) -I $(ASM_INC)
	@mv $(ASM_OBJS_NAME) $(ASM_OBJS_PATH)

$(VM_NAME): libftcreate $(VM_LIB) $(VM_OBJS)
	$(CC) -o $(VM_NAME) $(CFVM) $(CFLAGS) $(VM_LIB) $(VM_OBJS)
	@echo "\n\033[1;4mVM CREATED.\033[0m"

$(VM_OBJS): $(VM_SRCS) $(VM_INC)
	@mkdir $(VM_OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $(VM_SRCS) -I $(VM_INC)
	@mv $(VM_OBJS_NAME) $(VM_OBJS_PATH)

clean:
	@echo "\033[36;5mCleaning..."
	@make clean -C $(ASM_LIB_PATH)
	@make clean -C $(VM_LIB_PATH)
	@rm -f $(ASM_OBJS)
	@rmdir $(ASM_OBJS_PATH) 2> /dev/null || true
	@rm -f $(VM_OBJS)
	@rmdir $(VM_OBJS_PATH) 2> /dev/null || true
	@echo "\033[36;3m Cleaning Done !\033[0m"

fclean: clean
	@echo "\033[32;5mFcleaning..."
	@make fclean -C $(ASM_LIB_PATH)
	@make fclean -C $(VM_LIB_PATH)
	@rm -f $(ASM_NAME)
	@rm -f $(VM_NAME)
	@echo "\033[32;3m Fcleaning Done !\033[0m"

re: fclean all

norm:
	@norminette $(VM_SRCS) $(ASM_SRCS) $(VM_INC) $(ASM_INC) $(ASM_LIB_PATH) $(VM_LIB_PATH)

cursor:
	@echo "\x1b[?12;25h"
