/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmpfile_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:37:51 by sujilee           #+#    #+#             */
/*   Updated: 2021/05/31 14:39:55 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		get_file_name(char *name)
{
	int	i;
	int	path;

	i = 0;
	path = 0;
	while (name[i])
		if (name[i++] == '/')
			path++;
	i = 0;
	while (path && name[i])
		if (name[i++] == '/')
			path--;
	return (i);
}

int		get_sub_len(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '.')
		i++;
	return (i);
}
