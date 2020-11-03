/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 08:05:23 by joockim           #+#    #+#             */
/*   Updated: 2020/11/03 20:28:48 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_p3		reflect_ray(t_p3 ray, t_p3 normal)
{
	return (vsubstract(scal_x_vec(2 * vdot(normal, ray), normal), ray));
}

double		calc_specular(t_v3 ray, t_inter *inter, t_scene data, t_fig *lst)
{
	double	light;
	t_p3	direction;
	t_p3	p_to_cam;
	t_p3	reflected;

	direction = vsubstract(data.l->o, inter->p);
	p_to_cam = vsubstract(ray.o, inter->p);
	reflected = reflect_ray(direction, inter->normal);
	if (vdot(reflected, p_to_cam) > 0)
		light = data.l->br * pow(vcos(reflected, p_to_cam), lst->specular);
	else
		light = 0;
	return (light);
}

void		add_coefficient(double (*rgb)[3], double coef, int color)
{
	unsigned int	mask;

	mask = 255 << 16;
	(*rgb)[0] += coef * ((color & mask) >> 16) / 255;
	mask >>= 8;
	(*rgb)[1] += coef * ((color & mask) >> 8) / 255;
	mask >>= 8;
	(*rgb)[2] += coef * (color & mask) / 255;
}

int			is_light(t_p3 o, t_p3 d, t_fig *lst)
{
	double	in;

	while (lst)
	{
		if (lst->flag == SP)
			in = sphere_inter(o, d, lst);
		else if (lst->flag == PL)
			in = plane_inter(o, d, lst->fig.pl.p, lst->normal);
		else if (lst->flag == TR)
			in = triangle_inter(o, d, lst);
		else if (lst->flag == SQ)
			in = square_inter(o, d, lst);
		else if (lst->flag == CY)
			in = cylinder_inter(o, d, lst);
		else if (lst->flag == CU)
			in = cube_inter(o, d, lst);
		else if (lst->flag == PY)
			in = pyramid_inter(o, d, lst);
		if (in > EPSILON && in < 1)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void		compute_light(t_v3 ray, t_inter *inter, t_scene data, t_fig *lst)
{
	double	light;
	double	rgb[3];
	t_p3	direction;

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	add_coefficient(&rgb, data.ambient_light, data.al_color);
	while (data.l)
	{
		direction = vsubstract(data.l->o, inter->p);
		if (is_light(inter->p, direction, lst) && vdot(inter->normal, direction) > 0)
		{
			light = data.l->br * vcos(inter->normal, direction);
			add_coefficient(&rgb, light, data.l->color);
		}
		ray.o = ray.o;
		if (lst->specular)
		{
			light = calc_specular(ray, inter, data, lst);
			add_coefficient(&rgb, light, data.l->color);
		}
		data.l = data.l->next;
	}
	inter->color = color_x_light(inter->color, rgb);
}
