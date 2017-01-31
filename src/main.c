/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/31 15:49:34 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"

MATERIAL	*mtl_cube(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "cube")))
		return (m);
	m = new_material(s, "cube");
	m->base_map = load_image_file(f,
		"res/cube/cube_base.bmp");
	m->ao_map = load_image_file(f,
		"res/cube/cube_ao.bmp");
	m->rough_map = load_image_file(f,
		"res/cube/cube_rough.bmp");
	m->metal_map = load_image_file(f,
		"res/cube/cube_metal.bmp");
	m->normal_map = load_image_file(f,
		"res/cube/cube_normal.bmp");
	m->height_map = load_image_file(f,
		"res/cube/cube_height.bmp");
	m->alpha_map = load_image_file(f,
		"res/cube/cube_alpha.bmp");
	m->parallax = 0.5;
	m->refraction = 1.52f;
	m->refraction_color = (VEC3){1, 1, 1};
	m->uv_scale = (VEC2){1, 1};
	m->roughness = 0.03;
	m->metalness = 0.5;
	m->alpha = 1;
	return (m);
}

void	default_scene(char *file, ENGINE *engine)
{
	LIGHT		*l;

	if (access(file, 0 | F_OK | R_OK) != 0)
	{
		write(1, "Cannot find file !", 19); //TODO la aussi stp change avec un truc plus propre !
		exit(0);
	}
	create_scene(parser(file), engine);
	l = new_light(&engine->scene, POINT, (VEC3){2, 2, 2});
	l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	//l->color = (VEC3){1, 1, 1};
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->power = 2.f;
	l->attenuation = 0.02;
	l->falloff = 10;
	l->spot_size = 80;
	l->ambient_coef = 0.2f;
	/*scene->active_camera->transform->target = new_rttransform(scene,
		(VEC3){-200, 200, 200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});*/
}

inline VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution)
{
	return ((VEC2){
		(2 * ((float)(screen_coord.x + 0.5) / (float)resolution.x) - 1),
		(1 - 2 * ((float)(screen_coord.y + 0.5) / (float)resolution.y))});
}

void	fill_buffers(ENGINE *engine, t_point2 screen_coord, CAST_RETURN *ret)
{
	void	*bufferptr;

	if (ret->intersect.intersects)
	{
		bufferptr = get_buffer_value(engine->positionbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret->intersect.position;
		bufferptr = get_buffer_value(engine->normalbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret->intersect.normal;
		bufferptr = get_buffer_value(engine->depthbuffer, screen_coord);
		*((float *)bufferptr) = ret->intersect.distance[0];
		if (RENDER_NORMALS)
			put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(ret->intersect.normal, 1)));
	}
}

VEC3	compute_area_lighting(ENGINE *engine, CAST_RETURN *ret)
{
	UINT	i;
	UINT	max;
	VEC3	col;
	RAY		r;
	CAST_RETURN	castret;

	i = 0;
	col = new_vec3(0, 0, 0);
	r.origin = vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.005f));
	RAY		lray = new_ray(engine->active_scene->active_camera->transform->current.position, new_vec3(0, 1, 0));
	VEC3	ndir = ret->intersect.normal;
	UINT	hits = 0;
	max = engine->area_sampling;
	while (i < max)
	{
		castret = cast_light_ray(engine, engine->active_scene, r);
		if (castret.intersect.intersects && castret.mtl.alpha > 0.0001 && castret.mtl.emitting.power)
		{
			hits++;
			castret.mtl.emitting.position = castret.intersect.position;
			lray.direction = vec3_negate(r.direction);
			col = vec3_add(col, compute_point_color(castret.mtl.emitting, ret->mtl, ret->intersect, lray));
		}
		ndir = new_vec3(frand_a_b(-1, 1), frand_a_b(-1, 1), frand_a_b(-1, 1));
		r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn, ndir));
		i++;
	}
	if (hits)
		return (vec3_fdiv(col, hits));
	else return (col);
}

BOOL	scene_contains_area_light(SCENE *scene)
{
	UINT		i;
	ARRAY		primitives;
	RTPRIMITIVE	p;

	i = 0;
	primitives = scene->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		if (p.material
		&& p.material->emitting.power > 0
		&& p.material->emitting.color.x > 0
		&& p.material->emitting.color.y > 0
		&& p.material->emitting.color.z > 0)
			return (true);
		i++;
	}
	return (false);
}

/*static inline VEC4	pixel_color(ENGINE *e, CAST_RETURN *r, BOOL area_lights)
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

BOOL	render_scene(ENGINE *e, SCENE *scene)
{
	t_point2	scoord;
	CAMERA		cam;
	RTTRANSFORM	trans;
	BOOL		area_lights;
	FRAMEBUFFER	f;

	if (!scene->active_camera || !scene->active_camera->transform)
		return (false);
	cam = *scene->active_camera;
	e->active_scene = scene;
	update_rttransform(cam.transform);
	trans = *cam.transform;
	scoord = (t_point2){-1, -1};
	f = e->framebuffer;
	cam.m4_view = mat4_mult_mat4(trans.current.transform,
			mat4_perspective(cam.fov, f.size.y / (float)f.size.x, cam.znear, cam.zfar));
	area_lights = scene_contains_area_light(scene);
	while (scoord.y++ < f.size.y - 1)
	{
		scoord.x = -1;
		while (scoord.x++ < f.size.x - 1)
		{
			VEC2		nscoord;

			nscoord = normalize_screen_coord(scoord, f.size);
			cam.ray = new_ray(trans.current.position,
				mat4_mult_vec3(cam.m4_view, vec3_normalize((VEC3){nscoord.x, nscoord.y, -1})));
			CAST_RETURN	r;

			if ((r = cast_ray(e, scene, cam.ray)).intersect.intersects)
			{
				put_pixel_to_buffer(f, scoord, pixel_color(e, &r, area_lights));
				fill_buffers(e, scoord, &r);
			}
			else
				put_pixel_to_buffer(f, scoord, new_vec4(0, 0, 0, 1));
			e->progress_callback(e, (scoord.x + 1 + (scoord.y + 1) * f.size.y) / (float)(f.size.y * f.size.y + f.size.x));
			if (e->stop_rendering)
				return (false);
		}
	}
	return (true);
}*/

int		main(int argc, char *argv[])
{
	ENGINE			engine;
	t_engine_opt	options;
	t_callback		callback;

	options.window_size = options.internal_size = (t_point2){1024, 1024};
	options.max_refr = MAX_REFR;
	options.max_refl = MAX_REFL;
	options.area_sampling = 256;
	engine = new_engine(options);
	callback = new_callback(ssao, &engine);
	ezarray_push(&engine.post_treatments, &callback);
	callback = new_callback(depth_of_field, &engine);
	ezarray_push(&engine.post_treatments, &callback);
	callback = new_callback(bloom, &engine);
	ezarray_push(&engine.post_treatments, &callback);
	callback = new_callback(gamma_correction, &engine);
	ezarray_push(&engine.post_treatments, &callback);
	default_scene(argv[1], &engine);
	clear_renderer(&engine);
	if (render_scene(&engine, &engine.scene))
	{
		UINT	i = 0;
		while (i < engine.post_treatments.length)
		{
			do_post_treatment(&engine, ezarray_get_index(engine.post_treatments, i));
			if (i++ < engine.post_treatments.length)
				copy_framebuffer(engine.finalbuffer, engine.framebuffer);
		}
		display_framebuffer(engine.finalbuffer, engine.image);
		refresh_window(engine.window);
		framework_loop(engine.framework);
	}
	destroy_framework(engine.framework);
	destroy_engine(&engine);
	return (argv[argc - 1][0]);
}
