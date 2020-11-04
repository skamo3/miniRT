/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/11/05 00:14:08 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_mlx(t_mlx *mlx, t_scene *data)
{
	t_cam	*cam_begin;
	
	mlx->mlx_ptr = mlx_init();
	cam_begin = mlx->cam;
	mlx->begin = mlx->cam;
	data->xres = data->xres < WIN_SIZE_X ? data->xres : WIN_SIZE_X;
	data->yres = data->yres < WIN_SIZE_Y ? data->yres : WIN_SIZE_Y;
	while (mlx->cam)
	{
		mlx->cam->img_ptr = mlx_new_image(mlx->mlx_ptr, data->xres, data->yres);
		mlx->cam->px_img = (int *)mlx_get_data_addr(mlx->cam->img_ptr,
				&mlx->cam->bits_per_pixel, &mlx->cam->size_line, &mlx->cam->endian);
		mlx->cam = mlx->cam->next;
	}
	mlx->cam = cam_begin;
}

int		key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		ft_printf("Exit program with press \"esc\" key\n");
		exit(0);
	}
	mlx->cam = mlx->cam;
	return (1);
}

int		close_red_button()
{
	ft_printf("Exit program with press \"red button\"\n");
	exit(0);
	return (1);
}

void	start_mlx(t_mlx mlx, t_scene data)
{
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, data.xres, data.yres,
			"miniRT");
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.cam->img_ptr, 0, 0);
	mlx_hook(mlx.win_ptr, KEY_PRESS, 0, key_press, &mlx);
	mlx_hook(mlx.win_ptr, PRESS_RED_BUTTON, 0, close_red_button, 0); 
	mlx_loop(mlx.mlx_ptr);
}

int calc_pixel_color(int *edge_color, int last[2], t_wrap *w)
{
	t_rss	rss;
	int		*color;

	rss.limit = 3;
	rss.xres = w->data.xres;
	rss.yres = w->data.yres;
	rss.x = w->x;
	rss.y = w->y;
	w->data.bgr = 0x353535;
	color = sample_pixel(edge_color, last, rss, w);
	if (color_difference(color[0], color[3])
			|| color_difference(color[1], color[2]))
		return (supersample(color, rss, w));
	return (average_supersampled_color(color));
}

void	render_scene(t_wrap *w)
{
	int	edge_color[w->data.xres + 2];
	int	last[2];
	int	color;
	int	n;

	n = w->data.yres / THREAD_NUM;
	w->y = n * w->thread_id;
	while (w->y < (n * (w->thread_id + 1)))
	{
		w->x = 0;
		while (w->x < w->data.xres)
		{
			color = calc_pixel_color(edge_color, last, w);
			w->mlx.cam->px_img[w->y * w->data.xres + w->x] = color;
			w->x++;
		}
		if (w->thread_id == THREAD_NUM - 1)
			ft_printf("\rRendering scene (cam %d/%d) [%d%%]",
					w->mlx.cam->idx, w->data.cam_nb, 100 * (w->y % n) / n);
		w->y++;
	}
	if (w->thread_id == THREAD_NUM - 1)
		ft_printf("\rRendering scene (cam %d/%d) [100%%]\n",
				w->mlx.cam->idx, w->data.cam_nb);
	return ;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_scene	data;
	t_fig	*lst;
	t_wrap	wrapper[THREAD_NUM];

	if (ac < 2 || ac > 3)
		error_check(1, "");
	if (ac == 2 && ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3 ))
		error_check(2, "");
	if (ac == 3 && ft_strncmp(av[2], "--save", 6))
		error_check(3, "");
	parse(&mlx, &data, &lst, av);
	init_mlx(&mlx, &data);
	wrap_data(mlx, data, lst, wrapper);
	multithreading(wrapper);
	if (ac == 3)
	start_mlx(mlx, data);
	return (0);
}
