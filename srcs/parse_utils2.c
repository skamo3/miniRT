/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:30:31 by joockim           #+#    #+#             */
/*   Updated: 2020/10/15 19:34:55 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	skip_space(char **str)
{
	while (**str == 32 || (**str > 7 && **str < 13))
		(*str)++;
}

int		rt_atoi(char **str)
{
	int	minus;
	int	res;

	minus = 1;
	res = 0;
	skip_space(str);
	if (**str == '-' && *(*str)++)
		minus *= -1;
	while (**str >= '0' && **str <= '9')
	{
		res = res * 10 + (**str - '0');
		(*str)++;
	}
	return (res * minus);
}

double	rt_atof(char **str)
{
	int		minus;
	int		d;
	double	res;

	d = 0;
	minus = 1;
	skip_space(str);
	if (**str == '-' && *((*str)++))
		minus *= -1;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	if (**str == '.')
		(*str)++;
	res = 0.0;
	while (ft_isdigit(**str))
		res = res * 10 + (*((*str)++) - '0');
	while (res >= 1)
		res /= 10;
	res += d;
	return (res * minus);
}
