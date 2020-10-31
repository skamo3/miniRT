/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:13:43 by joockim           #+#    #+#             */
/*   Updated: 2020/11/01 01:19:34 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		try_all_inter(t_v3 ray, t_fig *lst, t_fig *close_fig, double *close_inter)
{
	double	distance;

	while (lst)
	{
		if (lst->flag == SP)
			distance = sphere_inter(ray.o, ray.d, lst);
		else if (lst->flag == PL)
			distance = plane_inter(ray.o, ray.d, lst->fig.pl.p, lst->normal);
		else if (lst->flag == TR)
			distance = triangle_inter(ray.o, ray.d, lst);
		else if (lst->flag == SQ)
			distance = square_inter(ray.o, ray.d, lst);
		else if (lst->flag == CY)
			distance = cylinder_inter(ray.o, ray.d, lst);
		else if (lst->flag == CU)
			distance = cube_inter(ray.o, ray.d, lst);
		else if (lst->flag == PY)
			distance = pyramid_inter(ray.o, ray.d, lst);
		if (distance > EPSILON && distance < *close_inter)
		{
			*close_fig = *lst;
			*close_inter = distance;
		}
		lst = lst->next;
	}
}

void	calc_normal(t_inter *inter, t_p3 d, t_fig *lst)
{
	if (lst->flag == SP)
	{
		inter->normal = normalize(vsubstract(inter->p, lst->fig.sp.c));
		if (vcos(d, inter->normal) > 0)
		{
			inter->normal = scal_x_vec(-1, inter->normal);
			lst->fig.sp.inside = 1;
		}
		else
			lst->fig.sp.inside = 0;
	}
	else
		inter->normal = vcos(d, lst->normal) > 0 ? scal_x_vec(-1, lst->normal)
			: lst->normal;
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
		if (lst->specular)
		{
			light = calc_specular(ray, inter, data, lst);
			add_coefficient(&rgb, light, data.l->color);
		}
		data.l = data.l->next;
	}
	inter->color = color_x_light(inter->color, rgb);
}

int			trace_ray(t_p3 o, t_p3 d, t_wrap *w, int depth)
{
	t_v3	ray;
	t_fig	close_fig;
	t_inter	inter;
	double	close_inter;
	double	r;

	ray.o = o;
	ray.d = d;
	close_inter = INFINITY;
	close_fig.flag = -1;
	try_all_inter(ray, w->lst, &close_fig, &close_inter);
	inter.p = vadd(o, scal_x_vec(close_inter, d));
	calc_normal(&inter, d, w->lst);
	inter.color = close_fig.flag != -1 ? close_fig.color : w->data.bgr;
	compute_light(ray, &inter, w->data, w->lst);
	depth = 0;
	r = 0;
	return (inter.color);
}
