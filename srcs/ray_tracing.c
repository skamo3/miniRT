/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:13:43 by joockim           #+#    #+#             */
/*   Updated: 2020/10/29 21:49:31 by joockim          ###   ########.fr       */
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
	return (x > 0 ? x : INFINITY);
}

int			point_out(t_p3 p1, t_p3 p2, t_p3 p3, t_p3 ip)
{
	t_p3	v1;
	t_p3	v2;
	t_p3	vp;
	
	v1 = vsubstract(p2, p1);
	v2 = vsubstract(p3, p1);
	vp = vsubstract(ip, p1);
	if (vdot(vcross(v1, v2), vcross(v1, vp)) < 0)
		return (1);
	return (0);
}

double		triangle_inter(t_p3 o, t_p3 d, t_fig *lst)
{
	double	id;
	t_p3	ip;

	id = plane_inter(o, d, lst->fig.tr.p1, lst->normal);
	ip = vadd(o, scal_x_vec(id, d));
	if (point_out(lst->fig.tr.p1, lst->fig.tr.p2, lst->fig.tr.p3, ip))
		return (INFINITY);
	if (point_out(lst->fig.tr.p2, lst->fig.tr.p3, lst->fig.tr.p1, ip))
		return (INFINITY);
	if (point_out(lst->fig.tr.p3, lst->fig.tr.p1, lst->fig.tr.p2, ip))
		return (INFINITY);
	return (id);
}

double		square_inter(t_p3 o, t_p3 d, t_fig *lst)
{
	t_p3		ip;
	t_sq_info	sq_info;
	double		id;
	double		cos1;
	double		limit;

	id = plane_inter(o, d, lst->fig.sq.c, lst->normal);
	ip = vadd(o, scal_x_vec(id, d));
	sq_info.floor = fabs(lst->normal.y) == 1 ? vdefine(1, 0, 0) : vdefine(0, 1, 0);
	sq_info.half_size = vcross(lst->normal, sq_info.floor);
	sq_info.center_to_ip = vsubstract(ip, lst->fig.sq.c);
	cos1 = fabs(vcos(sq_info.half_size, sq_info.center_to_ip));
	if (cos1 < sqrt(2) / 2)
		cos1 = cos(M_PI_2 - acos(cos1));
	limit = (lst->fig.sq.side / 2) / cos1;
	if (mod(sq_info.center_to_ip) <= limit)
		return (id);
	return (INFINITY);
}

int			solve_cylinder(double x[2], t_p3 o, t_p3 d, t_fig *lst)
{
	t_p3	v;
	t_p3	u;
	double	a;
	double	b;
	double	c;
	
	v = scal_x_vec(vdot(d, lst->fig.cy.nv), lst->fig.cy.nv);
	v = vsubstract(d, v);
	u = scal_x_vec(vdot(vsubstract(o, lst->fig.cy.c), lst->fig.cy.nv),
			lst->fig.cy.nv);
	u = vsubstract(vsubstract(o, lst->fig.cy.c), u);
	a = vdot(v, v);
	b = 2 * vdot(v, u);
	c = vdot(u, u) - pow(lst->fig.cy.r, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if (x[0] < EPSILON && x[1] < EPSILON)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

t_p3		calc_cy_normal(double x[2], t_p3 o, t_p3 d, t_fig *lst)
{
	double	dist;
	double	res;

	if ((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h) 
			&& (lst->fig.cy.dist2 >= 0 && lst->fig.cy.dist2 <= lst->fig.cy.h))
	{
		dist = x[0] < x[1] ? lst->fig.cy.dist1 : lst->fig.cy.dist2;
		res = x[0] < x[1] ? x[0] : x[1];
	}
	else if (lst->fig.cy.dist1 <= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h)
	{
		dist = lst->fig.cy.dist1;
		res = x[0];
	}
	else
	{
		dist = lst->fig.cy.dist2;
		res = x[1];
	}
	x[0] = res;
	return (normalize(vsubstract(vsubstract(scal_x_vec(res, d),
			scal_x_vec(dist, lst->fig.cy.nv)), vsubstract(lst->fig.cy.c, o))));
}

double		cy_intersection(t_p3 o, t_p3 d, t_p3 *normal, t_fig *lst)
{
	double	x[2];

	if (solve_cylinder(x, o, d, lst) == 0)
		return (INFINITY);
	lst->fig.cy.dist1 = vdot(lst->fig.cy.nv, vsubstract(scal_x_vec(x[0], d), vsubstract(lst->fig.cy.c, o)));
	lst->fig.cy.dist2 = vdot(lst->fig.cy.nv, vsubstract(scal_x_vec(x[1], d), vsubstract(lst->fig.cy.c, o)));
	if (!(lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h)
			|| (lst->fig.cy.dist2 >= 0 && lst->fig.cy.dist2 <= lst->fig.cy.h))
		return (INFINITY);
	*normal = calc_cy_normal(x, o, d, lst);
	return (x[0]);
}

double		caps_inter(t_p3 o, t_p3 d, t_fig *lst)
{
	double	id1;
	double	id2;
	t_p3	ip1;
	t_p3	ip2;
	t_p3	c2;

	c2 = vadd(lst->fig.cy.c, scal_x_vec(lst->fig.cy.h, lst->fig.cy.nv));
	id1 = plane_inter(o, d, lst->fig.cy.c, lst->fig.cy.nv);
	id2 = plane_inter(o, d, c2, lst->fig.cy.nv);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = vadd(o, scal_x_vec(id1, d));
		ip2 = vadd(o, scal_x_vec(id2, d));
		if ((id1 < INFINITY && distance(ip1, lst->>fig.cy.c) <= lst->fig.cy.r)
				&& (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY &&
				distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
			return (id1);
		else if (id2 < INFINITY &&
				distance(ip2, c2) <= lst->fig.cy.r)
			return (id2);
	}
	return (INFINITY);
}

double		cylinder_inter(t_p3 o, t_p3 d, t_fig *lst)
{
	double	cy_inter;
	double	caps_inter;
	t_p3	cy_normal;

	cy_inter = cy_intersection(o, d, &cy_normal, lst);
	if (lst->texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = caps_inter(o, d, lst);
	return (INFINITY);
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
			distance = triangle_inter(ray.o, ray.d, lst);
		else if (lst->flag == SQ)
			distance = square_inter(ray.o, ray.d, lst);
		else if (lst->flag == CY)
			distance = cylinder_inter(ray.o, ray.d, lst);
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
