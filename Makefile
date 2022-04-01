# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 14:54:02 by mgo               #+#    #+#              #
#    Updated: 2022/04/01 16:53:17 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CDEBUG		=	-fsanitize=address -g
RM			=	rm -rf

INC_LINK	=	-I./includes/
LIBFT		=	-L./lib/libft -lft

SRC_PATH	=	./srcs
SRC_LIST	=	main.c \
				set_data.c \
				parsing_quote.c \
				splitspace_remain.c \
				process.c \
				free_data.c \
				tool_function.c \
				exit.c
SRC			=	$(addprefix $(SRC_PATH)/, $(SRC_LIST))

OBJ_PATH	=	./obj
OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH)/, $(OBJ_LIST))

$(NAME)	:	$(OBJ) libft
	$(CC) $(CFLAGS) $(OBJ) $(INC_LINK) $(LIBFT) -o $(NAME)

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC_LINK) -c $< -o $@

libft	:
	@make -C ./lib/libft all

all		:	$(NAME)

bonus	:	$(NAME)

clean	:
	@make -C ./lib/libft clean
	@$(RM) $(OBJ_PATH)

fclean	:
	@make -C ./lib/libft fclean
	@$(RM) $(OBJ_PATH) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
