/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:13:43 by joockim           #+#    #+#             */
/*   Updated: 2020/10/24 20:49:28 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	solve_sphere(double x[2], t_p3 o, t_p3 d, t_fig *lst)
{
	double	disc;
	t_p3	oc;
	double	k[3];

	oc = vsubstract(o, lst->fig.sp.c);
	k[0] = vdot(d, d);
	k[1] = 2 * vdot(d, oc);
	k[2] = vdot(oc, oc) - lst->fig.sp.r * lst->fig.sp.r;
	disc = k[1] * k[1] - (4 * k[0] * k[2]);
	if (disc < 0)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return ;
	}
	x[0] = (-k[1] + sqrt(disc)) / (2 * k[0]);
	x[1] = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

double		sphere_inter(t_p3 o, t_p3 d, t_fig *lst)
{
	double	close;
	double	x[2];
	t_p3	ip1;
	t_p3	ip2;

	close = INFINITY;
	solve_sphere(x, o, d, lst);
	if (x[0] > EPSILON && x[0] < INFINITY)
		close = x[0];
	if (x[1] > EPSILON && x[1] < INFINITY)
		close = x[1] < x[0] ? x[1] : close;
	if (lst->texture != 4)
		return (close);
	ip1 = vadd(o, scal_x_vec(x[0], d));
	ip2 = vadd(o, scal_x_vec(x[1], d));
	if (ip1.y >= lst->fig.sp.c.y && ip2.y >= lst->fig.sp.c.y)
		return (x[0] < x[1] ? x[0] : x[1]);
	else if (ip1.y >= lst->fig.sp.c.y)
		return (x[0]);
	else if (ip2.y >= lst->fig.sp.c.y)
		return (x[1]);
	return (INFINITY);
}

double		plane_inter(t_p3 o, t_p3 d, t_p3 plane_p, t_p3 plane_nv)
{
	double	x;
	double	denom;

	denom = vdot(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (vdot(plane_nv, vsubstract(plane_p, o))) / denom;
	double a = vdot(plane_nv, vsubstract(plane_p, o));
	return (x > 0 ? x : INFINITY);
}

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
			;
		else if (lst->flag == SQ)
			;
		else if (lst->flag == CY)
			;
		else if (lst->flag == CU)
			;
		else if (lst->flag == PY)
			;
		if (distance > EPSILON && distance < *close_inter)
		{
			*close_fig = *lst;
			*close_inter = distance;
		}
		lst = lst->next;
	}
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

	depth = 0;
	r = 0;
	inter.color = 0;
	return (0);
}
