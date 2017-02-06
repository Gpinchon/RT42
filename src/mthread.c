/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:05:05 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/06 20:17:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <pthread.h>

t_point2	*get_scoords(t_point2 size)
{
	t_point2	*scoords;
	int			i;
	t_point2	p;
	t_point2	inc;

	scoords = (t_point2 *)malloc(NUM_THREADS * sizeof(t_point2));
	i = 0;
	p.y = 0;
	inc.x = size.x / DIV_THREADS;
	inc.y = size.y / DIV_THREADS;
	while (p.y < size.y)
	{
		p.x = 0;
		while (p.x < size.x)
		{
			scoords[i] = (t_point2){p.x, p.y};
			p.x += inc.x;
			i++;
		}
		p.y += inc.y;
	}
	return (scoords);
}

t_point2	*get_limits(t_point2 size)
{
	t_point2	*limits;
	int			i;
	t_point2	p;
	t_point2	inc;

	limits = (t_point2 *)malloc(NUM_THREADS * sizeof(t_point2));
	i = 0;
	p.y = size.y / DIV_THREADS;
	inc.x = size.x / DIV_THREADS;
	inc.y = size.y / DIV_THREADS;
	while (p.y <= size.y)
	{
		p.x = size.x / DIV_THREADS;
		while (p.x <= size.x)
		{
			limits[i] = (t_point2){p.x, p.y};
			p.x += inc.x;
			i++;
		}
		p.y += inc.y;
	}
	return (limits);
}

BOOL	join_threads(pthread_t *threads, ENGINE *e)
{
	int			t;
	void		*status;

	t = 0;
	while (t < NUM_THREADS)
	{
		e->progress_callback(e, t / (float)NUM_THREADS);
		if (pthread_join(threads[t], &status))
			return (false);
		e->progress_callback(e, t / (float)NUM_THREADS);
		if (e->stop_rendering)
			return (false);
		t++;
	}
	return (true);
}

void	*render_multithread(pthread_t *threads, ENGINE *e, SCENE *scene,
	BOOL area_lights)
{
	int			t;
	t_pth_args	*args;
	t_point2	*scoords;
	t_point2	*limits;

	t = 0;
	args = (t_pth_args *)malloc(NUM_THREADS * sizeof(t_pth_args));
	scoords = get_scoords(e->framebuffer.size);
	limits = get_limits(e->framebuffer.size);
	while (t < NUM_THREADS)
	{
		args[t].engine = memcpy(malloc(sizeof(ENGINE)), e, sizeof(ENGINE));
		args[t].scene = scene;
		args[t].scoord = scoords[t];
		args[t].limit = limits[t];
		args[t].area_lights = area_lights;
		if (pthread_create(&threads[t], NULL, render_part, (void *)&args[t]))
			return (NULL);
		t++;
	}
	free(scoords);
	free(limits);
	return (args);
}

BOOL	render_scene(ENGINE *e, SCENE *s)
{
	pthread_t	*th;
	t_pth_args	*arg;
	BOOL		ret;
	int			t;

	th = (pthread_t *)malloc(NUM_THREADS * sizeof(pthread_t));
	e->active_scene = s;
	ret = true;
	if (!(arg = render_multithread(th, e, s, scene_contains_area_light(s))))
		ret = false;
	if (!ret || !join_threads(th, e))
		ret = false;
	t = 0;
	while(t < NUM_THREADS)
	{
		free(arg[t].engine);
		t++;
	}
	if (arg)
		free(arg);
	free(th);
	return (ret);
}