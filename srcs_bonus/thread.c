/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joockim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 21:15:54 by joockim           #+#    #+#             */
/*   Updated: 2020/11/07 17:12:12 by joockim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

static void	*render_thread(void *ptr)
{
	t_wrap	*w;

	w = (t_wrap *)ptr;
	while (w->mlx.cam)
	{
		render_scene(w);
		w->mlx.cam = w->mlx.cam->next;
	}
	return (NULL);
}

void		multithreading(t_wrap *wrapper)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_create(&threads[i], NULL, render_thread, &wrapper[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
		pthread_join(threads[i++], NULL);
}

void		wrap_data(t_mlx mlx, t_scene data, t_fig *lst, t_wrap *wrapper)
{
	int i;

	i = 0;
	while (i < THREAD_NUM)
	{
		wrapper[i].mlx = mlx;
		wrapper[i].data = data;
		wrapper[i].lst = lst;
		wrapper[i].thread_id = i;
		i++;
	}
}
