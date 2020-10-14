/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:03:43 by joockim           #+#    #+#             */
/*   Updated: 2020/10/15 03:28:41 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VEC3_H_
# define _VEC3_H_

# include <math.h>

typedef struct	s_p3
{
	double	x;
	double	y;
	double	z;
}				t_p3;

typedef struct	s_v3
{
	t_p3	o;
	t_p3	d;
}				t_v3;

t_p3	vdefine(double x, double y, double z);
t_p3	vadd(t_p3 a, t_p3 b);
t_p3	vsubstract(t_p3 a, t_p3 b);
double	vdot(t_p3 a, t_p3 b);
t_p3	cross(t_p3 a, t_p3 b);
t_p3	scal_x_vec(t_p3 a, double t);
double	mod(t_p3 v);
t_p3	normalize(t_p3 v);
double	vcos(t_p3 a, t_p3 b);
double	vsin(t_p3 a, t_p3 b);
double	distance(t_p3 a, t_p3 b);
t_p3	x_axis_rotation(t_p3 v, double angle);
t_p3	y_axis_rotation(t_p3 v, double angle);
t_p3	z_axis_rotation(t_p3 v, double angle);
#endif
