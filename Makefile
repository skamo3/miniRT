# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joockim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/11 00:08:51 by joockim           #+#    #+#              #
#    Updated: 2020/10/12 17:37:54 by joockim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

CC = gcc

CFLAGS = -Wall -Werror -Wextra

UTILS = utils/

LIBFT_FLAGS = -L ${UTILS}libft -lft -L ${UTILS}libftprintf -lftprintf

MLX_FLAGS = -I minilibx -L ./minilibX -lmlx -framework OpenGL -framework AppKit

SRCS = $(addprefix ./srcs/, \
	   get_next_line.c \
	   main.c)

OBJS = ${SRCS:.c=.o}

FLAGS = ${CFLAGS} ${LIBFT_FLAGS} ${MLX_FLAGS}

.PHONY : all clean fclean re

${NAME} : ${OBJS}
	make -C ${UTILS}libft
	make -C ${UTILS}libftprintf
	${CC} ${FLAGS} ${OBJS} -o ${NAME}
	./RT ./scenes/sphere.rt

all : ${NAME}

clean :
	make clean -C ${UTILS}libft
	make clean -C ${UTILS}libftprintf
	rm -f ${OBJS}

fclean : clean
	make fclean -C ${UTILS}libft
	make fclean -C ${UTILS}libftprintf
	rm -rf ${NAME}

re : fclean all
