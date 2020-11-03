/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 08:17:17 by joockim           #+#    #+#             */
/*   Updated: 2020/11/04 01:20:45 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	color_x_light(int color, double rgb[3])
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

int	cproduct(int color, double coef)
{
	int	mask;
	int	r;
	int	g;
	int	b;

	mask = 255;
	r = coef * ((color & (mask << 16)) >> 16);
	g = coef * ((color & (mask << 8)) >> 8);
	b = coef * (color & mask);
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((r << 16) | (g << 8) | b);
}

int	cadd(int color_a, int color_b)
{
	int	mask;
	int	r;
	int	g;
	int	b;

	mask = 255;
	r = ((color_a & (mask << 16)) + (color_b & (mask << 16))) & (mask << 16);
	g = ((color_a & (mask << 8)) + (color_b & (mask << 8))) & (mask << 8);
	b = ((color_a & mask) + (color_b & mask)) & mask;
	return (r | g | b);
}
