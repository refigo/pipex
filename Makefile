# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 14:54:02 by mgo               #+#    #+#              #
#    Updated: 2021/12/18 13:45:27 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CDEBUG		=	-fsanitize=address -g
RM			=	rm -f

INC_LINK	=	-I./includes/
LIBFT		=	-L./lib/libft -lft

SRC_PATH	=	./srcs/
SRC_LIST	=	main.c \
				set_data.c \
				parsing_quote.c \
				splitspace_remain.c \
				process.c \
				free_data.c \
				tool_function.c \
				exit.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_LIST))
OBJ			=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ) libft
	$(CC) $(CFLAGS) $(OBJ) $(INC_LINK) $(LIBFT) -o $(NAME)

%.o		:	%.c
	$(CC) $(CFLAGS) $(INC_LINK) -c $< -o $@

libft	:
	@make -C ./lib/libft all

all		:	$(NAME)

clean	:
	@make -C ./lib/libft clean
	@$(RM) $(OBJ)

fclean	:	clean
	@make -C ./lib/libft fclean
	@$(RM) $(OBJ) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
