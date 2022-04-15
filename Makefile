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

RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[0;33m"
WHITE		=	"\033[0;37m"
BRED		=	"\033[1;31m"
BGREEN		=	"\033[1;32m"
BYELLOW		=	"\033[1;33m"
BWHITE		=	"\033[1;37m"
ENDCOLOR	=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

NAME		=	pipex

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		+=	-fsanitize=address -g
RM			=	rm -rf

INC_LINK	=	-I./includes/ -I./lib/libft/includes/
LIBFT		=	-L./lib/libft -lft

SRC_PATH	=	./srcs/
DIR_MAN		=	mandatory/
DIR_BNS		=	bonus/
OBJ_PATH	=	./obj/

SRC_LIST	=	main.c \
				set_data.c \
				heredoc.c \
				parsing_quote.c \
				splitspace_remain.c \
				run_pipex.c \
				process.c \
				free_data.c \
				func_pipe_pid.c \
				func_tool.c \
				func_exit.c
SRC			=	$(addprefix $(SRC_PATH)$(DIR_MAN), $(SRC_LIST))

B_SRC_LIST	=	main_bonus.c \
				set_data_bonus.c \
				heredoc_bonus.c \
				parsing_quote_bonus.c \
				splitspace_remain_bonus.c \
				run_pipex_bonus.c \
				process_bonus.c \
				free_data_bonus.c \
				func_pipe_pid_bonus.c \
				func_tool_bonus.c \
				func_exit_bonus.c
B_SRC		=	$(addprefix $(SRC_PATH)$(DIR_BNS), $(B_SRC_LIST))

OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH)$(DIR_MAN), $(OBJ_LIST))

B_OBJ_LIST	=	$(B_SRC_LIST:.c=.o)
B_OBJ		=	$(addprefix $(OBJ_PATH)$(DIR_BNS), $(B_OBJ_LIST))

$(OBJ_PATH)$(DIR_MAN)%.o	:	$(SRC_PATH)$(DIR_MAN)%.c
	@echo $(YELLOW) "Compling...\t" $< $(ENDCOLOR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)$(DIR_MAN) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_LINK) -c $< -o $@

$(OBJ_PATH)$(DIR_BNS)%.o	:	$(SRC_PATH)$(DIR_BNS)%.c
	@echo $(YELLOW) "Compling...\t" $< $(ENDCOLOR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)$(DIR_BNS) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_LINK) -c $< -o $@

$(NAME)	:	$(OBJ) libft
	@echo $(GREEN) "Source files are compiled!\n" $(ENDCOLOR)
	@echo $(YELLOW) "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(INC_LINK) $(LIBFT) $(OBJ) -o $(NAME)
	@echo $(GREEN) "$(NAME) is created for mandatory!\n" $(ENDCOLOR)

libft	:
	@make -C ./lib/libft all

all		:	$(NAME)

bonus	:	$(B_OBJ) libft
	@echo $(GREEN) "Source files are compiled!\n" $(ENDCOLOR)
	@echo $(YELLOW) "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(INC_LINK) $(LIBFT) $(B_OBJ) -o $(NAME)
	@echo $(GREEN) "$(NAME) is created for bonus!\n" $(ENDCOLOR)

clean	:
	@echo $(YELLOW) "Cleaning object files..." $(ENDCOLOR)
	@make -C ./lib/libft clean
	@$(RM) $(OBJ_PATH)
	@echo $(RED) "Object files are cleaned!\n" $(ENDCOLOR)

fclean	: clean
	@echo $(YELLOW) "Removing $(NAME)..." $(ENDCOLOR)
	@make -C ./lib/libft fclean
	@$(RM) $(OBJ_PATH) $(NAME)
	@echo $(RED) "$(NAME) is removed!\n" $(ENDCOLOR)

re		:	fclean all

.PHONY	:	all bonus clean fclean re
