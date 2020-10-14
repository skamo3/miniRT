/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/10/15 05:27:58 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/minirt.h"

void	error_check(int n, char *error_message)
{
	if (n == 1)
		ft_printf("Invalid argument : Wrong args\n");
	if (n == 2)
		perror("Check file name :");
	if (n == 3)
		ft_printf("Invalid argument : Wrong input 3rd arg\n");
	if (n == 4)
		ft_printf("Check rt file : %s\n", error_message);
	if (n == 5)
		ft_printf("Memory error : %s\n", error_message);
	if (n == 6)
		ft_printf("Check rt file : %s parameter out of range\n", error_message);
	exit(1);
}

void	skip_space(char **str)
{
	while (**str == 32 || (**str > 7 && **str < 13))
		(*str)++;
}

int		rt_atoi(char **str)
{
	int	minus;
	int	res;

	minus = 1;
	res = 0;
	skip_space(str);
	if (**str == '-' && *(*str)++)
		minus *= -1;
	while (**str >= '0' && **str <= '9')
	{
		res = res * 10 + (**str - '0');
		(*str)++;
	}
	return (res * minus);
}

void	parse_resolution(t_scene *data, char *str)
{
	if (data->res_init > 0)
		error_check(4, "Double declaration Resolution");
	data->res_init += 1;
	data->xres = rt_atoi(&str);
	skip_space(&str);
	data->yres = rt_atoi(&str);
}

double	rt_atof(char **str)
{
	int		minus;
	int		d;
	double	res;

	d = 0;
	minus = 1;
	skip_space(str);
	if (**str == '-' && *((*str)++))
		minus *= -1;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	if (**str == '.')
		(*str)++;
	res = 0.0;
	while (ft_isdigit(**str))
		res = res * 10 + (*((*str)++) - '0');
	while (res >= 1)
		res /= 10;
	res += d;
	return (res * minus);
}

void	check_values(double n, double min, double max, char *err)
{
	if (n < min || n > max)
		error_check(6, err);
}

void	comma(char **str)
{
	if (**str != ',')
		error_check(4, "Parameter have wrong format");
	(*str)++;
}

int		parse_color(char **str)
{
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	r |= rt_atoi(str);
	check_values(r, 0, 255, "color");
	r <<= 16;
	comma(str);
	g |= rt_atoi(str);
	check_values(g, 0, 255, "color");
	g <<= 8;
	comma(str);
	b |= rt_atoi(str);
	check_values(b, 0, 255, "color");
	return (r | g | b);
}

void	parse_ambient(t_scene *data, char *str)
{
	if (data->al_init > 0)
		error_check(4, "Double declaration Ambient lightning");
	data->al_init += 1;
	skip_space(&str);
	data->ambient_light = rt_atof(&str);
	check_values(data->ambient_light, 0, 1, "ambient lightning");
	data->al_color = parse_color(&str);
}

void	*err_malloc(unsigned int n)
{
	void	*ptr;

	ptr = malloc(n);
	if (ptr == NULL)
		error_check(5, "Fail to alloc memory");
	return (ptr);
}

t_p3	parse_p3(char **str)
{
	t_p3	p;

	p.x = rt_atof(str);
	comma(str);
	p.y = rt_atof(str);
	comma(str);
	p.z = rt_atof(str);
	return (p);
}

void	parse_camera(t_mlx *mlx, t_scene *data, char *str)
{
	t_cam	*elem;
	t_cam	*begin;
	int			idx;

	idx = 0;
	begin = mlx->cam;
	elem = err_malloc(sizeof(t_cam));
	elem->next = NULL;
	if (mlx->cam)
	{
		while (mlx->cam->next)
			mlx->cam = mlx->cam->next;
		idx = mlx->cam->idx;
		mlx->cam->next = elem;
	}
	else
		mlx->cam = elem;
	elem->idx = idx + 1;
	data->cam_nb = elem->idx;
	elem->o = parse_p3(&str);
	elem->nv = normalize(parse_p3(&str));
	elem->fov = rt_atoi(&str);
	check_values(elem->fov, 0, 180, "Camera FOV");
	mlx->cam = begin ? begin : elem;
}

void	ft_addnewlst_back(t_fig **alst)
{
	t_fig	*begin;
	t_fig	*elem;
	t_fig	*list;

	begin = *alst;
	list = *alst;
	elem = err_malloc(sizeof(t_fig));
	elem->next = NULL;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elem;
	}
	else
		begin = elem;
	*alst = begin;
}

void	parse_cylinder(t_fig **elem, char *str)
{
	t_fig	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = CY;
	lst->fig.cy.c = parse_p3(&str);
	lst->fig.cy.nv = normalize(parse_p3(&str));
	lst->fig.cy.r = rt_atof(&str) / 2;
	check_values(lst->fig.cy.r, 0, INFINITY, "Cylinder radius");
	lst->fig.cy.h = rt_atof(&str);
	check_values(lst->fig.cy.h, 0, INFINITY, "Cylinder height");
	lst->specular = rt_atof(&str);
	check_values(lst->specular, 0, INFINITY, "Cylinder specular");
	lst->refl_idx = rt_atof(&str);
	check_values(lst->refl_idx, 0, 1, "Cylinder reflection");
	lst->refr_idx = rt_atof(&str);
	check_values(lst->refr_idx, 0, INFINITY, "Cylinder refraction");
	lst->texture = rt_atoi(&str);
	check_values(lst->texture, 0, 5, "Cylinder texture");
	if (lst->texture == 2)
		lst->wavelength = rt_atof(&str);
	lst->color = parse_color(&str);
}

void	parse_cube(t_fig **elem, char *str)
{
	t_fig	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = CU;
	lst->fig.sq.c = parse_p3(&str);
	lst->fig.sq.side = rt_atof(&str);
	check_values(lst->fig.sq.side, 0, INFINITY, "Square side");
	lst->specular = rt_atoi(&str);
	check_values(lst->specular, 0, INFINITY, "Square specular");
	lst->refl_idx = rt_atof(&str);
	check_values(lst->refl_idx, 0, INFINITY, "Square reflection");
	lst->refr_idx = rt_atof(&str);
	check_values(lst->refr_idx, 0, INFINITY, "Square refraction");
	lst->texture = rt_atoi(&str);
	check_values(lst->texture, 0, 5, "Square texture");
	if (lst->texture == 2)
		lst->wavelength = rt_atof(&str);
	lst->color = parse_color(&str);
}

void	save_args(t_mlx *mlx, t_scene *data, t_fig **lst, char *str)
{
	*lst = NULL;
	data->l = NULL;
	mlx->cam = NULL;
	if (*str == 'R')
		parse_resolution(data, ++str);
	else if (*str == 'A')
		parse_ambient(data, ++str);
	else if (*str == 'c' && (*(str + 1) == 32 || *(str + 1) == 9))
		parse_camera(mlx, data, ++str);
	else if (*str == 'c' && *(str + 1) == 'y' && *(str++) && *(str++))
		parse_cylinder(lst, str);
	else if (*str == 'c' && *(str + 1) == 'u' && *(str++) && *(str++))
		parse_cube(lst, str);

}

void	parsing(t_mlx *mlx, t_scene *data, t_fig **lst, char *str)
{
	data->res_init = 0;
	data->al_init = 0;
	if (*str == '#' || *str == 0)
		return ;
	else
		save_args(mlx, data, lst, str);

}

void	parse(t_mlx *mlx, t_scene *data, t_fig **lst, char **av)
{
	char	*str;
	int		fd;

	*lst = NULL;
	data->l = NULL;
	mlx->cam = NULL;
	if ((fd = open(av[1], 0)) ==  -1)
		exit(1);
	while (get_next_line(fd, &str))
		parsing(mlx, data, lst, str);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_scene	data;
	t_fig	*lst;

	if (ac < 2 || ac > 3)
		error_check(1, "");
	if (ac == 2 && ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3 ))
		error_check(2, "");
	if (ac == 3 && ft_strncmp(av[2], "--save", 6))
		error_check(3, "");
	parse(&mlx, &data, &lst, av);
	return (0);
}
