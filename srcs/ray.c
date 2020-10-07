/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:30:12 by joockim           #+#    #+#             */
/*   Updated: 2020/09/30 22:39:12 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec3.h"
#include "../includes/ray.h"

int		hit_sphere(t_p3 center, double radius, t_ray r)
{
	t_p3 oc;

	oc = vsubstract(r.origin, center);
	float a = vdot(r.dir, r.dir);
	float b = 2.0 * vdot(oc, r.dir);
	float c = vdot(oc, oc) - radius * radius;
}

t_p3	ray_color(t_p3 dir)
{
	t_p3	unit_dir;
	t_p3	color;
	float	t;

	unit_dir = vunit(dir);
	t = 0.5 * (unit_dir.y + 1.0);
	color = vdefine(1.0, 1.0, 1.0);
	color.x *= 1.0 - (t * 0.5);
	color.y *= 1.0 - (t * 0.3);
	return (color);
}
