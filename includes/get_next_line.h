/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:24:30 by marvin            #+#    #+#             */
/*   Updated: 2020/10/11 06:26:25 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);
int		buf_check(char *buf);
void	ft_strdel(char **as);
int		get_line(char **str, char **line);
int		result(int len, int fd, char **str, char **line);

#endif
