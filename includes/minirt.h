/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:00:27 by joockim           #+#    #+#             */
/*   Updated: 2020/11/04 04:29:26 by joockim          ###   ########.fr       */
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

# define WIN_SIZE_X 2560
# define WIN_SIZE_Y 1440

# define THREAD_NUM 4

# define EPSILON 0.00001

# define REFLECTION_LIMIT 3

typedef	struct	s_v3
{
	t_p3	o;
	t_p3	d;
}				t_v3;

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

typedef struct	s_inter
{
	int		color;
	int		ref_color;
	t_p3	normal;
	t_p3	p;
}				t_inter;

typedef struct	s_sq_info
{
	t_p3	half_size;
	t_p3	floor;
	t_p3	center_to_ip;
}				t_sq_info;

typedef struct	s_cube
{
	t_fig	sq;
	t_p3	center;
	t_p3	normal[6];
}				t_cube;

typedef struct	s_pyr
{
	t_fig	sq;
	t_fig	tr;
	t_p3	vertex_point;
	t_p3	normal[5];
	t_p3	corner[4];
}				t_pyr;

void	error_check(int n, char *error_message);
void	check_values(double n, double min, double max, char *err);
void	comma(char **str);
int		parse_color(char **str);
void	*err_malloc(unsigned int n);
t_p3	parse_p3(char **str);
void	ft_addnewlst_back(t_fig **alst);
void	skip_space(char **str);
int		rt_atoi(char **str);
double	rt_atof(char **str);
void	parsing(t_mlx *mlx, t_scene *data, t_fig **lst, char *str);
void	parse(t_mlx *mlx, t_scene *data, t_fig **lst, char **av);
void	parse_resolution(t_scene *data, char *str);
void	parse_ambient(t_scene *data, char *str);
void	parse_camera(t_mlx *mlx, t_scene *data, char *str);
void	parse_light(t_scene **data, char *str);
void	parse_cylinder(t_fig **elem, char *str);
void	parse_sphere(t_fig **elem, char *str);
void	parse_square(t_fig **elem, char *str);
void	parse_plane(t_fig **elem, char *str);
void	parse_triangle(t_fig **elem, char *str);
void	parse_cube(t_fig **elem, char *str);
void	parse_pyramid(t_fig **elem, char *str);
void	save_args2(t_fig **lst, char *str);
void	save_args(t_mlx *mlx, t_scene *data, t_fig **lst, char *str);
void	multithreading(t_wrap *wrapper);
void	wrap_data(t_mlx mlx, t_scene data, t_fig *lst, t_wrap *wrapper);
void	render_scene(t_wrap *w);
int		*sample_pixel(int *edge_color, int last[2], t_rss rss, t_wrap *w);
int		calc_ray(int n, t_rss rss, t_wrap *w);
void	try_all_inter(t_v3 ray, t_fig *lst, t_fig *close_fig, double *close_inter);
int		trace_ray(t_p3 o, t_p3 d, t_wrap *w, int depth);
double	sphere_inter(t_p3 o, t_p3 d, t_fig *lst);
double	plane_inter(t_p3 o, t_p3 d, t_p3 plane_p, t_p3 plane_nv);
double	triangle_inter(t_p3 o, t_p3 d, t_fig *lst);
double	square_inter(t_p3 o, t_p3 d, t_fig *lst);
double	cylinder_inter(t_p3 o, t_p3 d, t_fig *lst);
double	cube_inter(t_p3 o, t_p3 d, t_fig *lst);
double	pyramid_inter(t_p3 o, t_p3 d, t_fig *lst);
t_p3	reflect_ray(t_p3 ray, t_p3 normal);
double	calc_specular(t_v3 ray, t_inter *inter, t_scene data, t_fig *lst);
void	add_coefficient(double (*rgb)[3], double coef, int color);
int		is_light(t_p3 o, t_p3 d, t_fig *lst);
void	compute_light(t_v3 ray, t_inter *inter, t_scene data, t_fig *lst);
int		color_x_light(int color, double rgb[3]);
void	apply_texture(int texture, t_inter *inter, t_fig *lst);
int		cproduct(int color, double coef);
int		cadd(int color_a, int color_b);
void	calc_normal(t_inter *inter, t_p3 d, t_fig *lst);
t_p3	refract_ray(t_p3 d, t_p3 normal, t_fig *lst);
int		main(int ac, char **av);
#endif
