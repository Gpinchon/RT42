/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/08 19:28:51 by gpinchon         ###   ########.fr       */
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
	if (!float_equal(denom, 0.f))
	{
		if ((t = vec3_dot(vec3_sub(cp.position, r.origin), normal) / denom) >= FLOAT_ZERO)
		{
			inter.intersects = 1;
			inter.distance[0] = inter.distance[1] = t;
			inter.position = intersect_compute_position(r, inter.distance[0]);
			inter.normal = plane_normal(inter.position, cp);
			if (denom < 0)
				inter.normal = vec3_negate(inter.normal);
		}
	}
	return (inter);
}

INTERSECT intersect_capped_cylinder(t_primitive cp, t_ray r)
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
	if (cp.size > 0)
	{
		i.distance[0] *= (vec3_length(vec3_sub(vec3_add(v[2], vec3_scale(v[3], i.distance[0])), v[0])) <= cp.size / 2.f);
		i.distance[1] *= (vec3_length(vec3_sub(vec3_add(v[2], vec3_scale(v[3], i.distance[1])), v[0])) <= cp.size / 2.f);
	}
	if (i.distance[0] <= 0)
	{
		i.position = intersect_compute_position(r, (i.distance[0] = i.distance[1]));
		i.normal = vec3_negate(cylinder_normal(i.position, cp));
	}
	else
	{
		i.position = intersect_compute_position(r, i.distance[0]);
		i.normal = cylinder_normal(i.position, cp);
	}
	if (i.distance[0] <= 0)
		i.normal = vec3_negate(i.normal);
	if (!(i.intersects = intersect_test(i.distance)))
	{
		cp.position = vec3_sub(cp.position, vec3_scale(cp.direction, cp.size / 2.f));
		/*cp.direction = vec3_sub(i.position, vec3_scale(cp.direction, cp.size / 2.f));
		cp.direction = vec3_normalize(vec3_sub(cp.direction, cp.position));*/
		//cp.position = vec3_sub(i.position, vec3_scale(i.normal, (cp.radius)));
		//printf("%f, %f, %f\n", cp.position.x, cp.position.y, cp.position.z);
		i = intersect_disc(cp, r);
		return (i);
	}
	return (i);
}

VEC3		cone_normal2(VEC3 inter, t_primitive obj)
{
	float	radius;
	VEC3	ctop;
	VEC3	qtop;

	ctop = vec3_sub(inter, obj.position);
	radius = vec3_dot((ctop), obj.direction);
	qtop = vec3_sub(ctop, vec3_scale(obj.direction, radius));
	return (vec3_normalize(vec3_fdiv(qtop, obj.radius)));
}

/*
	a	= D|D - (1+k*k)*(D|V)^2
	b/2	= D|X - (1+k*k)*(D|V)*(X|V)
	c	= X|X - (1+k*k)*(X|V)^2
*/

INTERSECT		intersect_cone1(t_primitive cp, t_ray r)
{
	INTERSECT	inter;
	VEC3	co = vec3_sub(r.origin, cp.position);
	float	rdpd = vec3_dot(r.direction, cp.direction);
	float	copd = vec3_dot(co, cp.direction);
	float	rad = 1 + cp.radius2;
	if ((inter.intersects = (solve_quadratic(vec3_dot(r.direction, r.direction) - rad * pow(rdpd, 2),
		2 * (vec3_dot(r.direction, co) - rad * rdpd * copd), vec3_dot(co, co) - rad * pow(copd, 2), inter.distance)
	&& intersect_test(inter.distance))))
	{
		if (inter.distance[0] <= 0)
			inter.distance[0] = inter.distance[1];
		inter.position = intersect_compute_position(r, inter.distance[0]);
		float	m = rdpd * inter.distance[0] + copd;
		if (vec3_dot(cp.direction, vec3_normalize(vec3_sub(inter.position, cp.position))) < 0)
			inter.intersects = 0;
		else if (cp.size >= 0)
			inter.intersects = (vec3_distance(cp.position, vec3_add(cp.position, vec3_scale(cp.direction, m))) <= cp.size);
		if (inter.intersects)
		{
			inter.normal = vec3_normalize(vec3_sub(vec3_sub(inter.position, cp.position), vec3_scale(cp.direction, rad * m)));
			//inter.normal = cone_normal2(inter.position, cp);
		}

		/*if ()
		printf("%f\n", vec3_distance(cp.position, vec3_add(cp.position, vec3_scale(cp.direction, rdpd * inter.distance[0] + copd))));*/
	}
	return (inter);
}

ENGINE		new_engine(t_engine_opt options)
{
	ENGINE	engine;

	memset(&engine, 0, sizeof(ENGINE));
	engine.framework = new_framework();
	engine.window = new_window(engine.framework, options.window_size.x, options.window_size.y, "RT");
	set_loop_hook(engine.framework, new_callback((void(*)(void*))refresh_window, engine.window));
	engine.progress_callback = print_progress;
	engine.loading_screen = load_image_file(engine.framework, "./res/loading_screen.bmp");
	engine.image = new_image(engine.framework, options.window_size.x, options.window_size.y);
	engine.framebuffer = new_framebuffer(unsigned_char, options.internal_size, 4);
	engine.positionbuffer = new_framebuffer(FLOAT, options.internal_size, 3);
	engine.normalbuffer = new_framebuffer(FLOAT, options.internal_size, 3);
	engine.depthbuffer = new_framebuffer(FLOAT, options.internal_size, 1);
	engine.mtlbuffer = new_framebuffer(FLOAT, options.internal_size, sizeof(t_mtl) / sizeof(float));
	attach_image_to_window(engine.window, engine.image);
	engine.inter_functions[cone] = intersect_cone1;
	engine.inter_functions[sphere] = intersect_sphere;
	engine.inter_functions[cylinder] = intersect_cylinder;
	engine.inter_functions[capped_cylinder] = intersect_capped_cylinder;
	engine.inter_functions[plane] = intersect_plane2;
	engine.inter_functions[triangle] = intersect_triangle;
	engine.inter_functions[disc] = intersect_disc;
	engine.uv_functions[cone] = cylinder_uv;
	engine.uv_functions[sphere] = sphere_uv;
	engine.uv_functions[cylinder] = cylinder_uv;
	engine.uv_functions[capped_cylinder] = cylinder_uv;
	engine.uv_functions[plane] = plane_uv;
	engine.uv_functions[disc] = plane_uv;
	engine.max_refl = options.max_refl;
	engine.max_refr = options.max_refr;
	engine.area_sampling = options.area_sampling;
	generate_poisson_disc(engine.poisson_disc, 64, 0.05f, new_vec2(0, 1));
	return (engine);
}
