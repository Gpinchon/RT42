/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/12 18:57:38 by gpinchon         ###   ########.fr       */
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

SCENE		new_scene(void)
{
	SCENE	scene;

	memset(&scene, 0, sizeof(SCENE));
	return (scene);
}

void		create_framebuffers(ENGINE *engine, t_engine_opt opt)
{
	engine->framebuffer = new_framebuffer(unsigned_char, opt.internal_size, 4);
	engine->finalbuffer = new_framebuffer(unsigned_char, opt.internal_size, 4);
	engine->hdrbuffer = new_framebuffer(FLOAT, opt.internal_size, 4);
	engine->positionbuffer = new_framebuffer(FLOAT, opt.internal_size, 3);
	engine->normalbuffer = new_framebuffer(FLOAT, opt.internal_size, 3);
	engine->depthbuffer = new_framebuffer(FLOAT, opt.internal_size, 1);
}

static inline void	compute_tp(OBJ p, t_ray r, TRANSFORM *tr, VEC3 *tp)
{
	tp[0] = mat4_mult_vec3(tr->transform, p.triangle.point[0]);
	tp[1] = mat4_mult_vec3(tr->transform, p.triangle.point[1]);
	tp[2] = mat4_mult_vec3(tr->transform, p.triangle.point[2]);
	tp[1] = vec3_sub(tp[1], tp[0]);
	tp[2] = vec3_sub(tp[2], tp[0]);
	tp[0] = vec3_sub(r.origin, tp[0]);
}

INTERSECT			intersect_triangle2(OBJ p, t_ray r, TRANSFORM *tr)
{
	VEC3		tp[3];
	VEC3		qvec;
	VEC3		pvec;
	VEC3		fact;
	INTERSECT	i;

	i = new_intersect();
	compute_tp(p, r, tr, tp);
	pvec = vec3_cross(r.direction, tp[2]);
	fact.z = 1 / vec3_dot(tp[1], pvec);
	fact.x = vec3_dot(tp[0], pvec) * fact.z;
	if (fact.x < 0 || fact.x > 1)
		return i;
	qvec = vec3_cross(tp[0], tp[1]);
	fact.y = vec3_dot(r.direction, qvec) * fact.z;
	if (fact.y < 0 || fact.x + fact.y > 1)
		return i;
	i.distance[0] = vec3_dot(tp[2], qvec) * fact.z;
	if (i.distance[0] <= 0)
		return (i);
	i.position = intersect_compute_position(r, i.distance[0]);
	i.normal = (VEC3){tp[1].y * tp[2].z - tp[1].z * tp[2].y,
						tp[1].z * tp[2].x - tp[1].x * tp[2].z,
						tp[1].x * tp[2].y - tp[1].y * tp[2].x};
	i.intersects = 1;
	return i;
}

VEC2		triangle_uv(t_obj o, INTERSECT i, TRANSFORM *tr)
{
	VEC3		tp[3];
	VEC2		uv;
	VEC3		v[3];
	float		d[5];
	float		invDenom;

	tp[0] = mat4_mult_vec3(tr->transform, o.triangle.point[0]);
	tp[1] = mat4_mult_vec3(tr->transform, o.triangle.point[1]);
	tp[2] = mat4_mult_vec3(tr->transform, o.triangle.point[2]);
	v[0] = vec3_sub(tp[2], tp[0]);
	v[1] = vec3_sub(tp[1], tp[0]);
	v[2] = vec3_sub(i.position, tp[0]);
	d[0] = vec3_dot(v[0], v[0]);
	d[1] = vec3_dot(v[0], v[1]);
	d[2] = vec3_dot(v[0], v[2]);
	d[3] = vec3_dot(v[1], v[1]);
	d[4] = vec3_dot(v[1], v[2]);
	invDenom = 1 / (d[0] * d[3] - d[1] * d[1]);
	uv.x = ((d[3] * d[2] - d[1] * d[4]) * invDenom);
	uv.y = ((d[0] * d[4] - d[1] * d[2]) * invDenom);
	return (uv);
}

void		assign_functions(ENGINE *engine)
{
	engine->inter_functions[cone] = intersect_cone;
	engine->inter_functions[sphere] = intersect_sphere;
	engine->inter_functions[cylinder] = intersect_cylinder;
	engine->inter_functions[plane] = intersect_plane;
	engine->inter_functions[triangle] = intersect_triangle2;
	engine->inter_functions[disc] = intersect_disc;
	engine->uv_functions[cone] = cylinder_uv;
	engine->uv_functions[sphere] = sphere_uv;
	engine->uv_functions[cylinder] = cylinder_uv;
	engine->uv_functions[plane] = plane_uv;
	engine->uv_functions[triangle] = triangle_uv;
	engine->uv_functions[disc] = plane_uv;
}

ENGINE		new_engine(t_engine_opt o)
{
	ENGINE	e;

	memset(&e, 0, sizeof(ENGINE));
	e.framework = new_framework();
	e.window = new_window(e.framework, o.window_size.x, o.window_size.y, "RT");
	set_loop_hook(e.framework, new_callback((void(*)(void*))refresh_window,
		e.window));
	e.progress_callback = print_progress;
	e.loading_screen = load_image_file(e.framework, "./res/loading_screen.bmp");
	e.image = new_image(e.framework, o.window_size.x, o.window_size.y);
	attach_image_to_window(e.window, e.image);
	create_framebuffers(&e, o);
	e.post_treatments = new_ezarray(other, 0, sizeof(t_callback));
	assign_functions(&e);
	e.max_refl = o.max_refl;
	e.max_refr = o.max_refr;
	e.area_sampling = o.area_sampling;
	generate_poisson_disc(e.poisson_disc, 64, 0.05f, new_vec2(0, 1));
	return (e);
}
