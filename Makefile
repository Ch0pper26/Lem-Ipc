# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/29 18:28:20 by eblondee          #+#    #+#              #
#    Updated: 2026/03/05 12:50:11 by eblondee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### --- VAR --- ###

EXEC := lem-ipc

SRCS :=	main.c \
		init.c \
		parsing.c \
		player.c \
		term_display.c \

OBJS := $(SRCS:.c=.o)

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g

RM := rm -f

### --- LIBFT --- ###

LIBFT_DIR = Libft/

LIBFT = libft.a

### --- PRINT --- ###

CR := "\r"$(CLEAR)

CLEAR := "\\033[0K"

BASENAME = `basename $@`

### --- RULES --- ###

all : $(EXEC)

$(EXEC):	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) -o $(EXEC) 
	@printf $(CR)"\e[1m\e[38;5;74m>>> $(EXEC) is created ! <<<\e[0m\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) $(LIBFT) --no-print-directory

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(CR)"\e[2m\e[38;5;32m>>>\e[0m $(BASENAME)%s \e[2m\e[38;5;32m<<<\e[0m"$(CLEAR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(RM) $(OBJS)
	@printf "\e[1m\e[38;5;29m>>> All object files of $(EXEC) are cleaned ! <<<\e[0m\n"

fclean : clean
	@$(RM) $(EXEC)
	@printf "\e[1m\e[38;5;36m>>> $(EXEC) is cleaned ! <<<\e[0m\n"

re : fclean all

.PHONY: all clean fclean re
