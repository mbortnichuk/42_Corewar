# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/01 16:52:48 by iosypenk          #+#    #+#              #
#    Updated: 2018/05/01 16:52:59 by iosypenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = corewar

ASM = asm

CC = gcc

CFLAGS = -Wall -Wextra -Werror

ASM_OBJ :=	$(patsubst %.c,%.o,$(wildcard ./*.c))								\
			$(patsubst %.c,%.o,$(wildcard ./assembler/*.c))						\

OBJ :=	$(patsubst %.c,%.o,$(wildcard ./*.c))									\
		$(patsubst %.c,%.o,$(wildcard ./Core/VM/*.c))							\
		$(patsubst %.c,%.o,$(wildcard ./Core/VIS/*.c))							\
		$(patsubst %.c,%.o,$(wildcard ./Core/instructions/*.c))					\

LIBFT = ./libft/libft.a

.PHONY: libft

all: libft $(ASM) $(VM)

$(ASM): $(ASM_OBJ)
	$(CC) $(CFLAGS) -o $(ASM) $(ASM_OBJ) $(LIBFT)
	
$(VM): $(OBJ)
	$(CC) $(CFLAGS) -o $(VM) $(OBJ) $(LIBFT) -lncurses

libft:
	make -C ./libft

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -f $(OBJ)
	rm -f $(ASM_OBJ)
	make clean -C ./libft

fclean: clean
	rm -f $(VM)
	rm -f $(ASM)
	make fclean -C ./libft

re: fclean all
