/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersample_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:29:35 by joockim           #+#    #+#             */
/*   Updated: 2020/11/04 23:30:43 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	average(int color1, int color2)
{
	int	average[3];
	int	mask;
	int	color[2];
	int	i;

	mask = 255;
	ft_memset(average, 0, 3 * sizeof(int));
	color[0] = color1;
	color[1] = color2;
	i = 0;
	while (i < 2)
	{
		average[0] += (color[i] & (mask << 16)) >> 16;
		average[1] += (color[i] & (mask << 8)) >> 8;
		average[2] += color[i] & mask;
		i++;
	}
	average[0] = average[0] / 2;
	average[1] = average[1] / 2;
	average[2] = average[2] / 2;
	return ((average[0] << 16) | (average[1] << 8) | average[2]);
}

int	average_supersampled_color(int *color)
{
	int	ss_color[3];
	int	mask;
	int	n;

	ft_memset(ss_color, 0, sizeof(int) * 3);
	mask = 255;
	n = 0;
	while (n < 4)
	{
		ss_color[0] += (color[n] & (mask << 16)) >> 16;
		ss_color[1] += (color[n] & (mask << 8)) >> 8;
		ss_color[2] += color[n] & mask;
		n++;
	}
	ss_color[0] = ss_color[0] / 4;
	ss_color[1] = ss_color[1] / 4;
	ss_color[2] = ss_color[2] / 4;
	free(color);
	return ((ss_color[0] << 16) | (ss_color[1] << 8) | ss_color[2]);
}
