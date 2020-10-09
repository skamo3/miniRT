/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:01:56 by joockim           #+#    #+#             */
/*   Updated: 2020/10/09 19:06:16 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../includes/ray.h"
#include "../includes/minirt.h"

void	open_check(int ac, char **av)
{
	int	len;

	if (ac < 2 || ac > 3)
	{
		write(1, "Invalid argument\n", 17);
		exit(1);
	}
	if (ac == 2 && ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3 ))
	{
		write(1, "Invalid argument : second argument\n", 35);
		exit(1);
	}
	if (ac == 3 && ft_strncmp(av[2], "--save", 6))
	{
		write(1, "Invalid argument : third argumnet must be --save\n", 49);
		exit(1);
	}
}

void	parsing(t_mlx *mlx, t_scene *data, t_fig **lst, char **av)
{
	char	*str;
	int		fd;

	*lst = NULL;
	data->l = NULL;
	mlx->cam = NULL;
	printf("%s\n", av[1]);
	if ((fd = open(av[1], 0)) ==  -1)
		exit(1);
	printf("%d\n", fd);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_scene	data;
	t_fig	*lst;

	open_check(ac, av);
	parsing(&mlx, &data, &lst, av);
	
	return (0);
}
