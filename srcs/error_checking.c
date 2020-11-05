/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:02:54 by joockim           #+#    #+#             */
/*   Updated: 2020/11/06 03:53:15 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	error_check(int n, char *error_message)
{
	ft_printf("Error\n");
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
	if (n == 7)
		ft_printf("Open error : %s\n", error_message);
	exit(1);
}

void	success_message(int ac)
{
	if (ac == 2)
	{
		ft_printf("\nminiRT make Scene successfully rendered with ");
		ft_printf("%d thread\n", THREAD_NUM);
		ft_printf("press ESC or click RED BUTTON to close program\n");
		ft_printf("press space to change another camera\n\n");
	}
	else
	{
		ft_printf("\nScene successfully saved to BMP file\n");
		ft_printf("You can check your file in \"images\" directory\n\n");
		exit(0);
	}
}

void	check_values(double n, double min, double max, char *err)
{
	if (n < min || n > max)
		error_check(6, err);
}

void	*err_malloc(unsigned int n)
{
	void	*ptr;

	ptr = malloc(n);
	if (ptr == NULL)
		error_check(5, "Fail to alloc memory");
	return (ptr);
}
