# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 14:54:02 by mgo               #+#    #+#              #
#    Updated: 2021/12/06 14:54:04 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
#CDEBUG	=	-fsanitize=address -g
RM		=	rm -f
NAME	=	pipex

HEADER	=	./includes/
FOLDER	=	./srcs/

#temporary
LIBFT	=	./srcs/mgo_libft/*.c
LIBFT_OBJ	=	$(LIBFT:.c=.o)

SRC	=	./srcs/*.c
SRC_OBJ	=	$(SRC:.c=.o)

%.o	:	%.c
	$(CC) -I $(HEADER) -o $@ -c $<

$(NAME)	:	$(SRC) $(LIBFT)
	$(CC) -I $(HEADER) -o $(NAME) $(SRC) $(LIBFT)

all	:	$(NAME)

clean	:
	$(RM) $(SRC_OBJ)

fclean	:	clean
	$(RM) $(NAME)

.PHONY	:	all clean fclean re
