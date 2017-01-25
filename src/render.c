/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:49:13 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/25 19:02:34 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <pthread.h>

void	*render_part(void *pth_args)
{
	t_point2	scoord;
	CAMERA		cam;
	RTTRANSFORM	trans;
	VEC2		nscoord;
	CAST_RETURN	r;
	VEC3		col;
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
			col = new_vec3(0, 0, 0);
			vml_memset(&r, 0, sizeof(CAST_RETURN));
			if ((r = cast_ray(args.engine, args.scene, cam.ray)).intersect.intersects)
			{
				get_ret_mtl(&r);
				if (args.area_lights && r.mtl.alpha > 0.0001)
					col = vec3_add(col, compute_area_lighting(args.engine, &r));
				col = vec3_add(col, compute_lighting(args.engine, &r));
				col = vec3_add(col, compute_reflection(args.engine, &r, &cam.ray));
				col = vec3_add(col, compute_refraction(args.engine, &r, &cam.ray, 1.f));
			}
			put_pixel_to_buffer(f, scoord, vec3_to_vec4(col, 1));
			fill_buffers(args.engine, scoord, &r);
			scoord.x++;
		}
		scoord.y++;
	}
	pthread_exit(NULL);
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

BOOL	join_threads(pthread_t *threads)
{
	int			t;
	int			rc;
	void		*status;

	t = 0;
	while (t < NUM_THREADS)
	{
		rc = pthread_join(threads[t], &status);
		if (rc)
			return (false);
		t++;
	}
	return (true);
}

BOOL	render_multithread(pthread_t *threads, ENGINE *e, SCENE *scene)
{
	int			t;
	t_pth_args	*args;
	t_point2	*scoords;
	t_point2	*limits;
	BOOL		area_lights;

	t = 0;
	args = (t_pth_args *)malloc(NUM_THREADS * sizeof(t_pth_args));
	scoords = get_scoords(e->framebuffer.size);
	limits = get_limits(e->framebuffer.size);
	area_lights = scene_contains_area_light(scene);
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
	free(args);
	return (true);
}

BOOL	render_scene(ENGINE *e, SCENE *scene)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(NUM_THREADS * sizeof(pthread_t));
	e->active_scene = scene;
	if (!render_multithread(threads, e, scene))
	{
		free(threads);
		return (false);
	}
	if (!join_threads(threads))
	{
		free(threads);
		return (false);
	}
	free(threads);
	return (true);
}