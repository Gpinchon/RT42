/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:49:13 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/25 23:54:26 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <pthread.h>

static inline VEC4	pixel_color(ENGINE *e, CAST_RETURN *r, BOOL area_lights)
{
	VEC3		col;

	get_ret_mtl(r);
	col = compute_lighting(e, r);
	col = vec3_add(col, compute_reflection(e, r, &r->ray));
	col = vec3_add(col, compute_refraction(e, r, &r->ray, 1.f));
	if (area_lights && r->mtl.alpha > 0.0001)
		col = vec3_add(col, compute_area_lighting(e, r));
	return (vec3_to_vec4(col, 1));
}

void	*render_part(void *pth_args)
{
	t_point2	scoord;
	CAMERA		cam;
	RTTRANSFORM	trans;
	VEC2		nscoord;
	CAST_RETURN	r;
	FRAMEBUFFER	f;
	t_pth_args	args;

	args = *((t_pth_args *)pth_args);
	scoord = args.scoord;
	if (!args.scene->active_camera || !args.scene->active_camera->transform)
		pthread_exit(NULL);
	cam = *args.scene->active_camera;
	update_rttransform(cam.transform);
	trans = *cam.transform;
	f = args.engine->framebuffer;
	cam.m4_view = mat4_mult_mat4(trans.current.transform,
			mat4_perspective(cam.fov, f.size.y / (float)f.size.x, cam.znear, cam.zfar));
	while (scoord.y < args.limit.y)
	{
		scoord.x = args.scoord.x;
		while (scoord.x < args.limit.x)
		{
			nscoord = normalize_screen_coord(scoord, f.size);
			cam.ray = new_ray(trans.current.position,
				mat4_mult_vec3(cam.m4_view, vec3_normalize((VEC3){nscoord.x, nscoord.y, -2})));
			if ((r = cast_ray(args.engine, args.scene, cam.ray)).intersect.intersects)
			{
				put_pixel_to_buffer(f, scoord, pixel_color(args.engine, &r, args.area_lights));
				fill_buffers(args.engine, scoord, &r);
			}
			else
				put_pixel_to_buffer(f, scoord, new_vec4(0, 0, 0, 1));
			scoord.x++;
		}
		scoord.y++;
	}
	pthread_exit(NULL);
	return (NULL);
}

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
		if (e->stop_rendering)
			return (false);
		if (pthread_join(threads[t], &status))
			return (false);
		t++;
	}
	return (true);
}

BOOL	render_multithread(pthread_t *threads, ENGINE *e, SCENE *scene,
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
			return (false);
		t++;
	}
	free(scoords);
	free(limits);
	//free(args);
	return (true);
}

BOOL	render_scene(ENGINE *e, SCENE *s)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(NUM_THREADS * sizeof(pthread_t));
	e->active_scene = s;
	if (!render_multithread(threads, e, s, scene_contains_area_light(s)))
	{
		free(threads);
		return (false);
	}
	if (!join_threads(threads, e))
	{
		free(threads);
		return (false);
	}
	free(threads);
	return (true);
}