# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblondee <eblondee@student.42angoulem      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 10:53:30 by eblondee          #+#    #+#              #
#    Updated: 2025/11/19 15:28:31 by eblondee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## --- SRCS --- ##########
########## --- LIBFT --- ##########
SRCS:=	./srcs/libft/ft_isalpha.c \
		./srcs/libft/ft_isdigit.c \
		./srcs/libft/ft_isalnum.c \
		./srcs/libft/ft_isascii.c \
		./srcs/libft/ft_isprint.c \
		./srcs/libft/ft_strlen.c \
		./srcs/libft/ft_memset.c \
		./srcs/libft/ft_bzero.c \
		./srcs/libft/ft_memcpy.c \
		./srcs/libft/ft_memmove.c \
		./srcs/libft/ft_strlcpy.c \
		./srcs/libft/ft_toupper.c \
		./srcs/libft/ft_tolower.c \
		./srcs/libft/ft_strchr.c \
		./srcs/libft/ft_strrchr.c \
		./srcs/libft/ft_strncmp.c \
		./srcs/libft/ft_memchr.c \
		./srcs/libft/ft_memcmp.c \
		./srcs/libft/ft_strlcat.c \
		./srcs/libft/ft_strnstr.c \
		./srcs/libft/ft_atoi.c \
		./srcs/libft/ft_strdup.c \
		./srcs/libft/ft_calloc.c \
		./srcs/libft/ft_substr.c \
		./srcs/libft/ft_strjoin.c \
		./srcs/libft/ft_strtrim.c \
		./srcs/libft/ft_split.c \
		./srcs/libft/ft_itoa.c \
		./srcs/libft/ft_strmapi.c \
		./srcs/libft/ft_striteri.c \
		./srcs/libft/ft_putchar_fd.c \
		./srcs/libft/ft_putstr_fd.c \
		./srcs/libft/ft_putendl_fd.c \
		./srcs/libft/ft_putnbr_fd.c \
		./srcs/libft/ft_lstnew.c \
		./srcs/libft/ft_lstadd_front.c \
		./srcs/libft/ft_lstsize.c \
		./srcs/libft/ft_lstlast.c \
		./srcs/libft/ft_lstadd_back.c \
		./srcs/libft/ft_lstdelone.c \
		./srcs/libft/ft_lstclear.c \
		./srcs/libft/ft_lstiter.c \
		./srcs/libft/ft_lstmap.c \

########## --- GNL --- ##########
SRCS += ./srcs/get_next_line/get_next_line.c \
		./srcs/get_next_line/get_next_line_utils.c \

########## --- PRINTF --- ##########
SRCS += ./srcs/printf/ft_printf.c \
		./srcs/printf/ft_printf_utils.c \
		./srcs/printf/ft_printf_utils_bis.c \
		
########## --- ERROR --- ##########
SRCS +=	./srcs/error/print_error.c \

########## --- LIBFT_LSTDC --- ##########
SRCS +=	./srcs/libft_lstdc/ft_create_lstdc.c \
		./srcs/libft_lstdc/ft_free_lstdc.c \
		./srcs/libft_lstdc/ft_add_lstdc.c \
		./srcs/libft_lstdc/ft_index_lstdc.c \
		./srcs/libft_lstdc/ft_move_in_lstdc.c \
		./srcs/libft_lstdc/ft_print_lstdc.c \
        ./srcs/libft_lstdc/ft_get_lstdc.c \
        ./srcs/libft_lstdc/ft_move_elem_lstdc.c \
        ./srcs/libft_lstdc/ft_merge_lstdc.c \
        ./srcs/libft_lstdc/ft_int_lstdc.c \
        ./srcs/libft_lstdc/ft_str_lstdc.c \
        ./srcs/libft_lstdc/ft_char_lstdc.c \
        ./srcs/libft_lstdc/ft_anything_to_void.c \
        ./srcs/libft_lstdc/ft_void_to_anything.c \

########## --- LIBFT_BIS --- ##########
SRCS += ./srcs/libft_bis/ft_atoll.c \
		./srcs/libft_bis/ft_strcmp.c \
		./srcs/libft_bis/ft_strcpy.c \
		./srcs/libft_bis/ft_search_int_in_tab.c \
		./srcs/libft_bis/ft_free.c \
		./srcs/libft_bis/ft_len.c \
		./srcs/libft_bis/ft_tabchar.c \
		./srcs/libft_bis/ft_splitters.c \

########## --- VAR --- ##########

OBJS := $(SRCS:.c=.o)

NAME := libft.a

CC	:= gcc

RM	:= rm -rf

INC := libft.h 

CFLAG := -Wall -Wextra -Werror -g -I.$(INC)

########## --- PRINT --- ##########

CR := "\r"$(CLEAR)

CLEAR := "\\033[0K"

BASENAME = `basename $@`

########## --- RULES --- ##########

all:	$(NAME)

$(NAME):	$(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf $(CR)"\e[1m\e[38;5;74m>>> $(NAME) is created ! <<<\e[0m\n"
	
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(CR)"\e[2m\e[38;5;32m>>>\e[0m $(BASENAME)%s \e[2m\e[38;5;32m<<<\e[0m"

clean:
	@$(RM) $(OBJS)
	@printf "\e[1m\e[38;5;29m>>> All object files of $(NAME) are cleaned ! <<<\e[0m\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\e[1m\e[38;5;36m>>> $(NAME) is cleaned ! <<<\e[0m\n"

re:	fclean all

.PHONY: all clean fclean re
