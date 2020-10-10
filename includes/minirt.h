/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:00:27 by joockim           #+#    #+#             */
/*   Updated: 2020/10/10 23:35:10 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINIRT_H_
# define _MINIRT_H_

# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include "vec3.h"
# include "figures.h"
# include <stdio.h>

typedef struct	s_fig
{
	int				flag;
	union u_fig		fig;
	int				color;
	t_p3			normal;
	struct s_fig	*next;
}				t_fig;

typedef struct		s_light
{
	t_p3			o;
	double			br;
	int				color;
	struct s_light	*next;
}					t_light;

typedef struct	s_cam
{
	int				i;
	t_p3			o;
	t_p3			nv;
	int				fov;
	void			*img_ptr;
	int				*px_img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	struct s_camera	*next;
}				t_cam;

typedef struct	s_scene
{
	int		res_init;
	int		xres;
	int		yres;
	int		cam_nb;
	t_light	*l;
	int		al_init;
	double	ambient_light;
	int		al_color;
	int		bgr;
}				t_scene;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_cam	*cam;
	t_cam	*begin;
}				t_mlx;

#endif
