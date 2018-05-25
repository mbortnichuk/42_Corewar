# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbortnic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 15:45:02 by mbortnic          #+#    #+#              #
#    Updated: 2018/05/25 03:00:45 by mbortnic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS = asm_binary_writer.c \
		asm_write_octal.c \
		asm_writer.c \
		mb_check_arg_and_error.c \
		mb_header_cpy.c \
		mb_instruction_checker.c \
		mb_instruction_name.c \
		mb_label_checker.c \
		mb_start_parse.c \
		mb_support_func.c \
		mb_support_func1.c \
		main.c

# OBJS = $(SRCS:.c=.o)
OBJS :=	$(patsubst %.c,%.o,$(wildcard ./*.c))

INCL = -I /libft/libft.h -I asm.h

LIBF = -L./libft/ -lft
LIBD = ../libft/

CFLAGS = -Wall -Wextra -Werror -g3 -Wno-missing-prototypes \
			-Qunused-arguments
			# -Wno-missing-prototypes - determines whether warnings are issued for missing prototypes.
			# -Qunused-arguments - to avoid superflous warnings of additionally forwarded gcc arguments.
			# -g3 - maximum debug information.

GCC = gcc
CC = $(GCC)

RM = rm -fv
		# -f ignoring nonexistent files and arguments, never prompt;
		# -v explain what is being done.

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBD)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBF) $(INCL)
	@ echo "\033[32;1masm is ready\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@

clean:
	make clean -C $(LIBD)
	$(RM) $(OBJS)
	@ echo "\033[33;1masm obj files are removed\033[0m"

fclean: clean
	make fclean -C $(LIBD)
	$(RM) $(NAME)
	@ echo "\033[31;m$(NAME) is deleted\033[0m"

re: fclean all
	@ echo "\033[36;1mre performed\033[0m"

norm:
	@ echo "\033[35;1mWait a sec.\033[0m"
	@ norminette *.c *.h ./libft/*.c *.h
	@ echo "\033[35;1mnorminette check finished\033[0m"

.PHONY: all clean fclean re norm
