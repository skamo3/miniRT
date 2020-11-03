/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:13:43 by joockim           #+#    #+#             */
/*   Updated: 2020/11/04 01:30:29 by joockim          ###   ########.fr       */
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

t_p3		refract_ray(t_p3 d, t_p3 normal, t_fig *lst)
{
	double	cosi;
	double	etai;
	double	etat;
	double	eta;
	double	k;

	cosi = vdot(d, normal);
	etai = 1;
	etat = lst->refr_idx;
	if (lst->fig.sp.inside == 1)
	{
		k = etai;
		etai = etat;
		etat = k;
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? reflect_ray(scal_x_vec(-1, d), normal) :
			vadd(scal_x_vec(eta, d), scal_x_vec(eta - (sqrt(k) / cosi), normal)));
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
	calc_normal(&inter, d, &close_fig);
	inter.color = close_fig.flag != -1 ? close_fig.color : w->data.bgr;
	apply_texture(close_fig.texture, &inter, w->lst);
	compute_light(ray, &inter, w->data, w->lst);
	r = close_fig.flag != -1 ? close_fig.refl_idx : 0;
	close_fig.refr_idx = close_fig.flag != -1 ? close_fig.refr_idx : 0;
	if (close_fig.refr_idx > 0)
		inter.color = trace_ray(inter.p, refract_ray(d, inter.normal, &close_fig), w, depth);
	if (r > 0 && depth > 0)
		inter.ref_color = trace_ray(inter.p, reflect_ray(scal_x_vec(-1, d), inter.normal), w, depth - 1);
	return (cadd(cproduct(inter.color, 1 - r), cproduct(inter.ref_color, r)));
}
