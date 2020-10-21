/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:08:10 by joockim           #+#    #+#             */
/*   Updated: 2020/10/21 19:24:53 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	*sample_first(int *edge_color, int last[2], t_rss rss, t_wrap *w)
{
	int	*color;

	color = (int *)err_malloc(sizeof(int) * 4);
	if (rss.y == w->data.yres / THREAD_NUM * w->thread_id)
	{
		color[0] = calc_ray(0, rss, w);
		color[1] = calc_ray(2, rss, w);
		color[2] = calc_ray(6, rss, w);
		color[3] = calc_ray(8, rss, w);
		last[0] = color[3];
		last[1] = color[1];
		edge_color[0] = color[2];
	}
	else
	{
		color[0] = edge_color[0];
		color[1] = edge_color[1];
		color[2] = calc_ray(6, rss, w);
		color[3] = calc_ray(8, rss, w);
		last[0] = color[3];
		edge_color[0] = color[2];
	}
	return (color);
}

static int	*sample_center(int *edge_color, int last[2], t_rss rss, t_wrap *w)
{
	int	*color;

	color = (int *)err_malloc(sizeof(int) * 4);
	if (rss.y == w->data.yres / THREAD_NUM * w->thread_id)
	{
		color[0] = last[1];
		color[1] = calc_ray(2, rss, w);
		color[2] = last[0];
		color[3] = calc_ray(8, rss, w);
		last[0] = color[3];
		last[1] = color[1];
		edge_color[rss.x] = color[2];
	}
	else
	{
		color[0] = edge_color[rss.x];
		color[1] = edge_color[rss.x + 1];
		color[2] = last[0];
		color[3] = calc_ray(4, rss, w);
		last[0] = color[3];
		edge_color[rss.x] = color[2];
	}
	return (color);
}

static int	*sample_last(int *edge_color, int last[2], t_rss rss, t_wrap *w)
{
	int	*color;

	color = (int *)err_malloc(sizeof(int) * 4);
	if (rss.y == w->data.yres / THREAD_NUM * w->thread_id)
	{
		color[0] = last[1];
		color[1] = calc_ray(2, rss, w);
		color[2] = last[0];
		color[3] = calc_ray(8, rss, w);
		edge_color[rss.x] = color[2];
		edge_color[rss.x + 1] = color[3];
	}
	else
	{
		color[0] = edge_color[rss.x];
		color[1] = edge_color[rss.x + 1];
		color[2] = last[0];
		color[3] = calc_ray(3, rss, w);
		edge_color[rss.x] = color[2];
		edge_color[rss.x + 1] = color[3];
	}
	return (color);
}

int		*sample_pixel(int *edge_color, int last[2], t_rss rss, t_wrap *w)
{
	int	*color;
	printf("%d\n", rss.x);
	if (rss.x == 0)
		color = sample_first(edge_color, last, rss, w);
	else if (rss.x == w->data.xres - 1)
		color = sample_last(edge_color, last, rss, w);
	else
		color = sample_center(edge_color, last, rss, w);
	return (color);

}
