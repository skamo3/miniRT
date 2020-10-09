/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:24:30 by marvin            #+#    #+#             */
/*   Updated: 2020/10/09 18:39:48 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *string);
int		get_next_line(int fd, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		buf_check(char *buf);
void	ft_strdel(char **as);
int		get_line(char **str, char **line);
int		result(int len, int fd, char **str, char **line);

#endif
