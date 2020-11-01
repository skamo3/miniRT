/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 08:17:17 by joockim           #+#    #+#             */
/*   Updated: 2020/11/01 08:17:53 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			color_x_light(int color, double rgb[3])
{
	unsigned int	mask;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	mask = 255 << 16;
	r = rgb[0] * ((color & mask) >> 16);
	mask >>= 8;
	g = rgb[1] * ((color & mask) >> 8);
	mask >>= 8;
	b = rgb[2] * (color & mask);
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((r << 16) | (g << 8) | b);
}
