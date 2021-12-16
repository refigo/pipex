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

NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
#CDEBUG	=	-fsanitize=address -g
RM		=	rm -f

D_INC	=	./includes/
D_SRC	=	./srcs/
D_LIBFT	=	./includes/libft_mgo/

LIBFT_LIST	=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c
LIBFT		=	$(addprefix $(D_LIBFT), $(LIBFT_LIST))
LIBFT_OBJ	=	$(LIBFT:.c=.o)

SRC_LIST	=	main.c \
				set_data.c \
				process.c \
				free_data.c \
				exit.c
SRC			=	$(addprefix $(D_SRC), $(SRC_LIST))
SRC_OBJ		=	$(SRC:.c=.o)

$(NAME)	:	$(SRC_OBJ) $(LIBFT_OBJ)
	$(CC) $(CFLAGS) -I $(D_INC) $(SRC_OBJ) $(LIBFT_OBJ) -o $(NAME)

all		:	$(NAME)

%.o		:	%.c
	$(CC) $(CFLAGS) -I $(D_INC) -c $< -o $@

clean	:
	$(RM) $(SRC_OBJ) $(LIBFT_OBJ)

fclean	:	clean
	$(RM) $(NAME)

.PHONY	:	all clean fclean re
