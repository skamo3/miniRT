/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:29:38 by joockim           #+#    #+#             */
/*   Updated: 2020/10/30 19:32:19 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int		solve_cylinder(double x[2], t_p3 o, t_p3 d, t_fig *lst)
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

static t_p3		calc_cy_normal(double x[2], t_p3 o, t_p3 d, t_fig *lst)
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

static double	cy_intersection(t_p3 o, t_p3 d, t_p3 *normal, t_fig *lst)
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

static double	caps_intersection(t_p3 o, t_p3 d, t_fig *lst)
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
		if ((id1 < INFINITY && distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
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

double			cylinder_inter(t_p3 o, t_p3 d, t_fig *lst)
{
	double	cy_inter;
	double	caps_inter;
	t_p3	cy_normal;

	cy_inter = cy_intersection(o, d, &cy_normal, lst);
	if (lst->texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = caps_intersection(o, d, lst);
	if (cy_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cy_inter < caps_inter)
		{
			lst->normal = cy_normal;
			return (cy_inter);
		}
		lst->normal = lst->fig.cy.nv;
		return (caps_inter);
	}
	return (INFINITY);
}
