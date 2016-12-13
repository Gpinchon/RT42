/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 12:41:53 by gpinchon         ###   ########.fr       */
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

INTERSECT	intersect_plane2(t_primitive cp, t_ray r)
{
	INTERSECT	inter;
	t_vec3		normal;
	float		denom;
	float		t;

	inter = new_intersect();
	normal = vec3_negate(cp.direction);
	denom = vec3_dot(normal, r.direction);
	if (denom > FLOAT_ZERO)
	{
		if ((t = vec3_dot(vec3_sub(cp.position, r.origin), normal) / denom) >= FLOAT_ZERO)
		{
			inter.intersects = 1;
			inter.distance[0] = inter.distance[1] = t;
			inter.position = intersect_compute_position(r, inter.distance[0]);
			inter.normal = plane_normal(inter.position, cp);
		}
	}
	return (inter);
}

INTERSECT intersect_cylinder2(t_primitive cp, t_ray r)
{
	t_vec3		v[6];
	INTERSECT	i;

	i = new_intersect();
	v[0] = vec3_proj(cp.position, cp.direction);
	v[1] = vec3_sub(cp.position, v[0]);
	v[2] = vec3_proj(r.origin, cp.direction);
	v[3] = vec3_proj(r.direction, cp.direction);
	v[4] = vec3_sub(r.direction, v[3]);
	v[5] = vec3_sub(vec3_sub(r.origin, v[2]), v[1]);
	if (!(i.intersects = solve_quadratic(vec3_dot(v[4], v[4]),
		vec3_dot(v[5], v[4]) * 2.0, vec3_dot(v[5], v[5]) - (cp.radius2), i.distance)))
		return (i);
	if (cp.size > 0 && vec3_length(vec3_sub(vec3_add(v[2],
		vec3_scale(v[3], i.distance[0])), v[0])) >= cp.size / 2)
		i.distance[0] = 0;
	if (cp.size > 0 && vec3_length(vec3_sub(vec3_add(v[2],
		vec3_scale(v[3], i.distance[1])), v[0])) >= cp.size / 2)
		i.distance[1] = 0;
	if (!(i.intersects = intersect_test(i.distance)))
		return (i);
	if (i.distance[0] <= 0)
	{
		i.distance[0] = i.distance[1];
		i.position = intersect_compute_position(r, i.distance[0]);
		i.normal = vec3_negate(cylinder_normal(i.position, cp));
	}
	else
	{
		i.position = intersect_compute_position(r, i.distance[0]);
		i.normal = cylinder_normal(i.position, cp);
	}
	return (i);
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
	engine.inter_functions[sphere] = intersect_sphere;
	engine.inter_functions[cylinder] = intersect_cylinder2;
	engine.inter_functions[plane] = intersect_plane;
	engine.inter_functions[triangle] = intersect_triangle;
	engine.max_refl = MAX_REFL;
	engine.max_refr = MAX_REFR;
	return (engine);
}
