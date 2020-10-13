/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/10/14 01:40:38 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/ray.h"
#include "../includes/minirt.h"

void	error_check(int n)
{
	if (n == 1)
		ft_printf("Invalid argument : Wrong args\n");
	if (n == 2)
		perror("Check file name :");
	if (n == 3)
		ft_printf("Invalid argument : Wrong input 3rd arg\n");
	if (n == 4)
		ft_printf("Check rt file : Invalid format\n");
	exit(1);
}


void	parse_resolution(t_scene *data, char *str)
{
	int		flag;
	char	**s;

	flag = 0;
	s = ft_split(str, ' ');
	if (data->res_init > 0)
		error_check(4);
	data->res_init += 1;
	while (*s)
	{
		if (flag == 0)
			data->xres = ft_atoi(*s);
		else if (flag == 1)
			data->yres = ft_atoi(*s);
		flag++;
		s++;
	}
}

double	ft_atof(char *str)
{
	int		minus;
	int		d;
	double	res;

	res = 0;
	minus = 1;
	while (*str == 32 || (*str > 7 && *str < 13))
		str++;
	if (*str == '-' && str++;)
		minus *= -1;
	while (ft_isdigit(*str))
		d = d * 10 + ((*str)++ - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
		res = res * 10 + ((*str)++ - '0');
	while (res >= 1)
		res /= 10;
	d += res;
	return (res * minus);
}

void	parse_ambient(t_scene *data, char *str)
{
	int		flag;
	char	**s;

	flag = 0;
	s = ft_split(str, ' ');
	if (data->al_init > 0)
		error_check(4);
	data->al_init += 1;
	printf("%s\n", str);
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

}

void	parsing(t_mlx *mlx, t_scene *data, t_fig **lst, char *str)
{
	data->res_init = 0;
	data->al_init = 0;
	if (*str == '#' || *str == 0)
		return ;
	else
		save_args(mlx, data, lst, str);

	*lst = NULL;
	mlx->cam = NULL;


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
		error_check(1);
	if (ac == 2 && ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3 ))
		error_check(2);
	if (ac == 3 && ft_strncmp(av[2], "--save", 6))
		error_check(3);
	parse(&mlx, &data, &lst, av);

	return (0);
}
