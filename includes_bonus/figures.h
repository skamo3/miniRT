/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:19:47 by joockim           #+#    #+#             */
/*   Updated: 2020/11/07 17:12:44 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "minirt_bonus.h"

typedef struct	s_sp
{
	t_p3	c;
	double	r;
	int		inside;
}				t_sp;

typedef struct	s_pl
{
	t_p3	p;
}				t_pl;

typedef struct	s_sq
{
	t_p3	c;
	double	side;
}				t_sq;

typedef struct	s_cy
{
	t_p3	c;
	t_p3	nv;
	double	r;
	double	h;
	double	dist1;
	double	dist2;
}				t_cy;

typedef struct	s_tr
{
	t_p3	p1;
	t_p3	p2;
	t_p3	p3;
}				t_tr;

union			u_fig
{
	t_sp	sp;
	t_pl	pl;
	t_sq	sq;
	t_cy	cy;
	t_tr	tr;
};

#endif
