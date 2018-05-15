# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/26 16:39:49 by iosypenk          #+#    #+#              #
#    Updated: 2017/10/26 16:39:54 by iosypenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRCS :=	$(patsubst %.c,%.o,$(wildcard *.c))										\
		$(patsubst %.c,%.o,$(wildcard get_next_line/*.c))						\
		$(patsubst %.c,%.o,$(wildcard ft_printf/*.c))							\

all: $(NAME)

$(NAME): $(SRCS)
	@ar -cru $(NAME) $(SRCS)
	@ranlib $(NAME)
	@echo "\033[32mlibft.a compiled\033[0m"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf *.o
	@rm -rf *~
	@rm -rf a.out
	@rm -rf get_next_line/*.o
	@rm -rf ft_printf/*.o
	@echo "\033[32mclean completed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[32mfclean completed\033[0m"
	
re: fclean all
