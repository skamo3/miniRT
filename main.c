/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/09/29 18:27:25 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "./includes/vec3.h"

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
}	t_mlx;

t_mlx app;

int	main()
{
	const int	image_width = 256;
	const int	image_height = 256;
	t_p3		pixel_color;

	app.mlx_ptr = mlx_init();
	app.win_ptr = mlx_new_window(app.mlx_ptr, image_width, image_height, "PPM image");
	app.img_ptr = mlx_new_image(app.mlx_ptr, image_width, image_height);
	app.data = (int *)mlx_get_data_addr(app.img_ptr, &app.bpp, &app.size_l, &app.endian);

	int j = 0;
	while (j < image_height)
	{
		int i = 0;
		while (i < image_width)
		{
			float r = (double)i / (image_width - 1); // 0.0 ~1.0
			float g = (image_height -(double)j - 1) / (image_height - 1); // 1.0~0.0
			float b = 0.25; // constant

			int ir = 255.999 * r;
			int ig = 255.999 * g;
			int ib = 255.999 * b;

			pixel_color.x = ir * 256 * 256;
			pixel_color.y = ig * 256;
			pixel_color.z = ib;

			int color = pixel_color.x + pixel_color.y + pixel_color.z;
			app.data[j * 256 + i] = mlx_get_color_value(app.mlx_ptr, color);
			++i;
		}
		++j;
	}
	mlx_put_image_to_window(app.mlx_ptr, app.win_ptr, app.img_ptr, 0, 0);
	mlx_loop(app.mlx_ptr);
}
