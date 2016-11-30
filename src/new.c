/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/30 10:13:38 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

FRAMEBUFFER	new_framebuffer(TYPE type, t_point2 size, Uint8 depth)
{
	FRAMEBUFFER	buffer;

	buffer.array = new_ezarray(type, size.x * size.y * depth);
	buffer.size = size;
	buffer.opp = depth;
	buffer.bpp = buffer.opp * 8;
	buffer.sizeline = size.x * buffer.opp;
	return (buffer);
}

SCENE		new_scene()
{
	SCENE	scene;

	memset(&scene, 0, sizeof(SCENE));
	return (scene);
}

INTERSECT	intersect_sphere2(t_primitive s, t_ray r)
{
	t_vec3		eye;
	INTERSECT	inter;

	inter = new_intersect();
	eye = vec3_sub(r.origin, s.position);
	if (!(inter.intersects = solve_quadratic(
				vec3_dot(r.direction, r.direction),
				vec3_dot(eye, r.direction) * 2.0,
				vec3_dot(eye, eye) - (s.radius2),
				inter.distance) && intersect_test(inter.distance)))
		return (inter);
	if (inter.distance[0] <= 0)
	{
		inter.distance[0] = inter.distance[1];
		inter.position = intersect_compute_position(r, inter.distance[0]);
		inter.normal = vec3_negate(sphere_normal(inter.position, s));
	}
	else
	{
		inter.position = intersect_compute_position(r, inter.distance[0]);
		inter.normal = sphere_normal(inter.position, s);
	}
	return (inter);
}

ENGINE		new_engine()
{
	ENGINE	engine;

	memset(&engine, 0, sizeof(ENGINE));
	engine.framework = new_framework();
	engine.window = new_window(engine.framework, WINDOW_SIZE.x, WINDOW_SIZE.y, "RT");
	assign_loop_hook(engine.framework, new_callback((void(*)(void*))refresh_window, engine.window));
	engine.image = new_image(engine.framework, BUFFER_SIZE.x, BUFFER_SIZE.y);
	engine.framebuffer = new_framebuffer(unsigned_char, BUFFER_SIZE, 4);
	engine.positionbuffer = new_framebuffer(FLOAT, BUFFER_SIZE, 3);
	engine.normalbuffer = new_framebuffer(FLOAT, BUFFER_SIZE, 3);
	engine.mtlbuffer = new_framebuffer(FLOAT, BUFFER_SIZE, sizeof(t_mtl) / sizeof(float));
	attach_image_to_window(engine.window, engine.image);
	engine.inter_functions[cone] = intersect_cone;
	engine.inter_functions[sphere] = intersect_sphere2;
	engine.inter_functions[cylinder] = intersect_cylinder;
	engine.inter_functions[plane] = intersect_plane;
	engine.inter_functions[triangle] = intersect_triangle;
	return (engine);
}
