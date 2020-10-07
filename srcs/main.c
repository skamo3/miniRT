/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/10/07 09:50:30 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/vec3.h"
#include "../includes/ray.h"

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
	float		aspect_ratio = 16.0 / 9.0;
	const int	image_width = 256;
	const int	image_height = 256;

	float		viewport_height = 2.0;
	float		viewport_width = aspect_ratio * viewport_height;
	float		focal_length = 1.0;

	t_p3		origin = vdefine(0, 0, 0);
	t_p3		horizontal = vdefine(viewport_width, 0, 0);
	t_p3		vertical = vdefine(0, viewport_height, 0);
	t_p3		lower_left_corner;
	lower_left_corner.x = origin.x - horizontal.x / 2 - vertical.x / 2;
	lower_left_corner.y = origin.y - horizontal.y / 2 - vertical.y / 2;
	lower_left_corner.z = origin.z - horizontal.z / 2 - vertical.z / 2 - focal_length;

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
			float u = (double)i / (image_width - 1);
			float v = (image_height - (double)j - 1) / (image_height - 1);

			t_p3 ray;
			ray = lower_left_corner;
			ray = vadd(ray, vscalarmul(horizontal, u));
			ray = vadd(ray, vscalarmul(vertical, v));
			ray = vsubstract(ray, origin);
			ray = ray_color(ray);

			int ir = 255.999 * ray.x;
			int ig = 255.999 * ray.y;
			int ib = 255.999 * ray.z;
			
			pixel_color.x = ir * 256 * 256;
			pixel_color.y = ig * 256;
			pixel_color.z = ib;

			int color = pixel_color.x + pixel_color.y + pixel_color.z;
			app.data[j * image_width + i] = mlx_get_color_value(app.mlx_ptr, color);
			++i;
		}
		++j;
	}
	mlx_put_image_to_window(app.mlx_ptr, app.win_ptr, app.img_ptr, 0, 0);
	mlx_loop(app.mlx_ptr);
}
