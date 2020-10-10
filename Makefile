# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joockim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/11 00:08:51 by joockim           #+#    #+#              #
#    Updated: 2020/10/11 06:33:25 by joockim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = gcc

CFLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -I minilibx -L ./minilibX -lmlx -framework OpenGL -framework AppKit


SRCS = $(addprefix ./srcs/, \
	   get_next_line.c \
	   main.c)

OBJS = ${SRCS:.c=.o}

.PHONY : all clean fclean 

${NAME} : ${OBJS}
	make -C libft
	${CC} ${MLX_FLAGS} ${OBJS} -o ${NAME}

all : ${NAME}
