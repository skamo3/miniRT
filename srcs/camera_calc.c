/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:19:59 by joockim           #+#    #+#             */
/*   Updated: 2020/10/21 21:38:40 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_p3	set_camera(int n, t_rss rss, t_mlx mlx)
{
	double	asp_ratio;
	double	correct_fov;
	double	x_offset;
	double	y_offset;
	t_p3	p;

	x_offset = ((n % 3) * 0.5);
	y_offset = ((n / 3) * 0.5);
	asp_ratio = (double)rss.xres / (double)rss.yres;
	correct_fov = tan((mlx.cam->fov * M_PI / 180) / 2);
	printf("%d\n", mlx.cam->fov);
	printf("- : %f\n", mlx.cam->fov * M_PI / 180);
	printf("-- : %f\n", (mlx.cam->fov * M_PI / 180) / 2);
	printf("tan : %f\n", tan((mlx.cam->fov * M_PI / 180) / 2));
	printf("%f\n", correct_fov);
	rss.x = 0;
	mlx.mlx_ptr = 0;
	p.x = 0;

	return (p);
}

int	calc_ray(int n, t_rss rss, t_wrap *w)
{
	t_p3	d;
	int		color;

	color = 0;
	d = set_camera(n, rss, w->mlx);
	return (0);
}
