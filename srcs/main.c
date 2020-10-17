/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/10/18 01:58:22 by joockim          ###   ########.fr       */
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

void	wrap_data(t_mlx mlx, t_scene data, t_fig *lst, t_wrap *wrapper)
{
	int i;

	i = 0;
	while (i < THREAD_NUM)
	{
		wrapper[i].mlx = mlx;
		wrapper[i].data = data;
		wrapper[i].lst = lst;
		wrapper[i].thread_id = i;
		i++;	
	}
}

void	multithreading(t_wrap wrapper[THREAD_NUM])
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_create(&threads[i], NULL, render_thread, &wrapper[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
		pthread_join(threads[i++], NULL);
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
	return (0);
}
