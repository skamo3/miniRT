/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:00:27 by joockim           #+#    #+#             */
/*   Updated: 2020/10/21 19:21:04 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../utils/libft/libft.h"
# include "../utils/libftprintf/include/ft_printf.h"
# include "get_next_line.h"
# include "../utils/vec/vec3.h"
# include "figures.h"
# include "key_code.h"
# include <pthread.h>
# include <stdio.h>

# define SP 0
# define PL 1
# define SQ 2
# define TR 3
# define CY 4
# define CU 5
# define PY 6

# define WIN_SIZE_X 1920
# define WIN_SIZE_Y 1080

# define THREAD_NUM 1

# define EPSILON 0.00001

typedef struct	s_fig
{
	int				flag;
	union u_fig		fig;
	int				color;
	t_p3			normal;
	int				specular;
	double			refl_idx;
	double			refr_idx;
	int				texture;
	double			wavelength;
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
	int				idx;
	t_p3			o;
	t_p3			nv;
	int				fov;
	void			*img_ptr;
	int				*px_img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	struct s_cam	*next;
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

typedef struct	s_wrap
{
	t_mlx	mlx;
	t_scene	data;
	t_fig	*lst;
	int		thread_id;
	int		x;
	int		y;
}				t_wrap;

typedef struct	s_rss
{
	int	limit;
	int	xres;
	int	yres;
	int	x;
	int	y;
}				t_rss;

void		error_check(int n, char *error_message);
void		check_values(double n, double min, double max, char *err);
void		comma(char **str);
int			parse_color(char **str);
void		*err_malloc(unsigned int n);
t_p3		parse_p3(char **str);
void		ft_addnewlst_back(t_fig **alst);
void		skip_space(char **str);
int			rt_atoi(char **str);
double		rt_atof(char **str);
void		parsing(t_mlx *mlx, t_scene *data, t_fig **lst, char *str);
void		parse(t_mlx *mlx, t_scene *data, t_fig **lst, char **av);
void		parse_resolution(t_scene *data, char *str);
void		parse_ambient(t_scene *data, char *str);
void		parse_camera(t_mlx *mlx, t_scene *data, char *str);
void		parse_light(t_scene **data, char *str);
void		parse_cylinder(t_fig **elem, char *str);
void		parse_sphere(t_fig **elem, char *str);
void		parse_square(t_fig **elem, char *str);
void		parse_plane(t_fig **elem, char *str);
void		parse_triangle(t_fig **elem, char *str);
void		parse_cube(t_fig **elem, char *str);
void		parse_pyramid(t_fig **elem, char *str);
void		save_args2(t_fig **lst, char *str);
void		save_args(t_mlx *mlx, t_scene *data, t_fig **lst, char *str);
void		multithreading(t_wrap *wrapper);
void		wrap_data(t_mlx mlx, t_scene data, t_fig *lst, t_wrap *wrapper);
void		render_scene(t_wrap *w);
int			*sample_pixel(int *edge_color, int last[2], t_rss rss, t_wrap *w);
int			calc_ray(int n, t_rss rss, t_wrap *w);
int		main(int ac, char **av);
#endif
