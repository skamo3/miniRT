/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:24:30 by marvin            #+#    #+#             */
/*   Updated: 2020/04/27 18:28:29 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len;
	char	*res;

	len = ft_strlen(s1) + ft_strlen(s2);
	if ((res = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	i = 0;
	while (len--)
	{
		if (*s1 != 0)
			res[i] = *s1++;
		else
			res[i] = *s2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *string)
{
	size_t	len;
	char	*s;
	char	*ret;

	len = ft_strlen(string);
	if ((s = (char *)malloc(sizeof(char) * len + 1)) == 0)
		return (0);
	ret = s;
	while (len--)
		*s++ = *string++;
	*s = 0;
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*res;

	if (len == 0)
	{
		res = malloc(sizeof(char));
		*res = 0;
		return (res);
	}
	if ((res = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	i = 0;
	if (start < (unsigned int)ft_strlen(s))
	{
		while (len--)
			res[i++] = s[start++];
	}
	res[i] = '\0';
	return (res);
}
