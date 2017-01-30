/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:49:13 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/30 15:09:48 by gpinchon         ###   ########.fr       */
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

static inline void	render_pixel(t_pth_args args, CAMERA cam, FRAMEBUFFER f, t_point2 scoord)
{
	CAST_RETURN	r;
	VEC2		nscoord;

	nscoord = normalize_screen_coord(scoord, f.size);
	cam.ray.direction = mat4_mult_vec3(cam.m4_view,
		vec3_normalize((VEC3){nscoord.x, nscoord.y, -2}));
	if ((r = cast_ray(args.engine, args.scene, cam.ray)).intersect.intersects)
	{
		put_pixel_to_buffer(f, scoord, pixel_color(args.engine, &r, args.area_lights));
		fill_buffers(args.engine, scoord, &r);
	}
	else
		put_pixel_to_buffer(f, scoord, new_vec4(0, 0, 0, 1));
}

void	*render_part(void *pth_args)
{
	t_point2	scoord;
	CAMERA		c;
	FRAMEBUFFER	f;
	t_pth_args	args;

	args = *((t_pth_args *)pth_args);
	scoord.y = args.scoord.y - 1;
	if (!args.scene->active_camera || !args.scene->active_camera->transform)
		pthread_exit(NULL);
	c = *args.scene->active_camera;
	update_rttransform(c.transform);
	c.ray.origin = c.transform->current.position;
	f = args.engine->framebuffer;
	c.m4_view = mat4_mult_mat4(c.transform->current.transform,
	mat4_perspective(c.fov, f.size.y / (float)f.size.x, c.znear, c.zfar));
	while (++scoord.y < args.limit.y)
	{
		scoord.x = args.scoord.x - 1;
		while (++scoord.x < args.limit.x)
			render_pixel(args, c, f, scoord);
	}
	pthread_exit(NULL);
	return (NULL);
}
