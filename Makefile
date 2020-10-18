# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joockim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/11 00:08:51 by joockim           #+#    #+#              #
#    Updated: 2020/10/18 21:33:00 by joockim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

UTILS = utils/

LIBFT_FLAGS = -L ${UTILS}libft -lft -L ${UTILS}libftprintf -lftprintf -L ${UTILS}vec -lvec

MLX_FLAGS = -I minilibx -L ./minilibX -lmlx -framework OpenGL -framework AppKit

SRCS = $(addprefix ./srcs/, \
	   get_next_line.c \
	   error_checking.c \
	   parse1.c \
	   parse2.c \
	   parse3.c \
	   parse4.c \
	   parse_utils1.c \
	   parse_utils2.c\
	   main.c)

OBJS = ${SRCS:.c=.o}

FLAGS = ${CFLAGS} ${LIBFT_FLAGS} ${MLX_FLAGS}

.PHONY : all clean fclean re

${NAME} : ${OBJS}
	make -C ${UTILS}libft
	make -C ${UTILS}libftprintf
	make -C ${UTILS}vec
	${CC} ${FLAGS} ${OBJS} -o ${NAME}
	./RT ./scenes/everything.rt

all : ${NAME}

clean :
	make clean -C ${UTILS}libft
	make clean -C ${UTILS}libftprintf
	make clean -C ${UTILS}vec
	rm -f ${OBJS}

fclean : clean
	make fclean -C ${UTILS}libft
	make fclean -C ${UTILS}libftprintf
	make fclean -C ${UTILS}vec
	rm -rf ${NAME}

re : fclean all
