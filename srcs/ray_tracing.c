/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:13:43 by joockim           #+#    #+#             */
/*   Updated: 2020/11/01 09:01:09 by joockim          ###   ########.fr       */
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

static t_p3	sinwave(t_inter *inter, t_fig *lst)
{
	double	sinn;
	double	scal;

	scal = lst->wavelength;
	sinn = sin(inter->p.z * scal) + sin(inter->p.y * scal);
	return (x_axis_rotation(inter->normal, sinn));
}

static int	checkerboard(t_inter *inter)
{
	int		black;
	int		white;
	t_p3	coords;
	t_p3	val;
	int		party_mix;

	party_mix = 0;
	black = 0x000000;
	white = 0xffffff;
	coords.x = abs((int)floor(inter->p.x));
	coords.y = abs((int)floor(inter->p.y));
	coords.z = abs((int)floor(inter->p.z));
	val.x = (int)coords.x % 2;
	val.y = (int)coords.y % 2;
	val.z = (int)coords.z % 2;
	if (fabs(inter->normal.x) > 0)
		party_mix = (int)val.y ^ (int)val.z;
	else if (fabs(inter->normal.y) > 0)
		party_mix = (int)val.x ^ (int)val.y;
	return (party_mix ? black : white);
}

static void	define_color(double r, double g, double b, double color[3])
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

int			rainbow(t_inter *inter)
{
	double	color[3];
	double	w;

	w = 540 - (inter->normal.y * 160);
	if (w >= 380 && w < 440)
		define_color(-(w - 440) / (440. - 380.), 0.0, 1.0, color);
	else if (w >= 440 && w < 490)
		define_color(0.0, (w - 440.) / (490. - 440.), 1.0, color);
	else if (w >= 490 && w < 510)
		define_color(0.0, 1.0, -(w - 510.) / (510. - 490.), color);
	else if (w >= 510 && w < 540)
		define_color((w - 510.) / (540. - 510.), 1.0, 0.0, color);
	else if (w >= 540 && w < 645)
		define_color(1.0, -(w - 645.) / (645. - 540.), 0.0, color);
	else if (w >= 645 && w < 700)
		define_color(1.0, 0.0, 0.0, color);
	else
		define_color(0.0, 0.0, 0.0, color);
	color[0] *= 255;
	color[1] *= 255;
	color[2] *= 255;
	return (((int)color[0] << 16) | ((int)color[1] << 8) | (int)color[2]);
}

void		apply_texture(int texture, t_inter *inter, t_fig *lst)
{
	if (texture == 1)
		inter->color = checkerboard(inter);
	else if (texture == 2)
		inter->normal = sinwave(inter, lst);
	else if (texture == 3)
		inter->color = rainbow(inter);
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
	apply_texture(close_fig.texture, &inter, w->lst);
	compute_light(ray, &inter, w->data, w->lst);
	depth = 0;
	r = 0;
	return (inter.color);
}
