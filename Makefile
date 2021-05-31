# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/31 14:39:35 by sujilee           #+#    #+#              #
#    Updated: 2021/05/31 14:39:55 by sujilee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

BONUS_NAME = miniRT_bonus

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
	   parse_utils1.c \
	   parse_utils2.c\
	   sample_pixel.c \
	   camera_calc.c \
	   ray_tracing.c \
	   sphere.c \
	   pl_sq_tr.c \
	   cylinder.c \
	   light_calc.c \
	   color_calc.c \
	   make_bmpfile.c \
	   make_bmpfile_utils.c \
	   mlx_func1.c \
	   minirt.c)

BONUS_SRCS = $(addprefix ./srcs_bonus/, \
	   get_next_line.c \
	   error_checking.c \
	   parse1.c \
	   parse2.c \
	   parse3.c \
	   parse4.c \
	   parse_utils1.c \
	   parse_utils2.c\
	   thread.c \
	   sample_pixel.c \
	   camera_calc.c \
	   ray_tracing.c \
	   sphere.c \
	   pl_sq_tr.c \
	   cylinder.c \
	   compound_inter.c \
	   light_calc.c \
	   color_calc.c \
	   texture.c \
	   supersample.c \
	   supersample_utils.c \
	   make_bmpfile.c \
	   make_bmpfile_utils.c \
	   mlx_func1.c \
	   minirt.c)

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

FLAGS = ${CFLAGS} ${LIBFT_FLAGS} ${MLX_FLAGS}

.PHONY : all clean fclean re

${NAME} : ${OBJS}
	make -C ${UTILS}libft
	make -C ${UTILS}libftprintf
	make -C ${UTILS}vec
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

all : ${NAME}

${BONUS_NAME} : ${BONUS_OBJS}
	make -C ${UTILS}libft
	make -C ${UTILS}libftprintf
	make -C ${UTILS}vec
	${CC} ${FLAGS} ${BONUS_OBJS} -o ${BONUS_NAME}

bonus : ${BONUS_NAME}

clean :
	make clean -C ${UTILS}libft
	make clean -C ${UTILS}libftprintf
	make clean -C ${UTILS}vec
	rm -f ${OBJS}
	rm -f ${BONUS_OBJS}

fclean : clean
	make fclean -C ${UTILS}libft
	make fclean -C ${UTILS}libftprintf
	make fclean -C ${UTILS}vec
	rm -f ${NAME}
	rm -f ${BONUS_NAME}

re : fclean all
