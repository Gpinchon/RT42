/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/15 16:05:26 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	mat4_print(MAT4 m)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		printf("%c%f\t", !(i % 4) ? '\n' : 0, m.m[i]);
		i++;
	}
	printf("\n\n");
}

void	blit_buffer_scaled(FRAMEBUFFER buffer, void *image)
{
	t_rgba		rgbacol;
	UCHAR		*bufpixel;
	VEC2		coord;
	VEC2		imgcoord;
	t_point2	imgsize;

	imgsize = get_image_data(image).size;
	coord = new_vec2(0, 0);
	imgcoord = new_vec2(0, 0);
	while (imgcoord.y < imgsize.y)
	{
		coord.x = 0;
		imgcoord.x = 0;
		while (imgcoord.x < imgsize.x)
		{
			bufpixel = get_buffer_value(buffer, (t_point2){coord.x, coord.y});
			rgbacol = rgba(bufpixel[2], bufpixel[1], bufpixel[0], bufpixel[3]);
			put_image_pixel(image, &rgbacol, (t_point2){imgcoord.x, imgcoord.y});
			coord.x += (float)buffer.size.x / (float)imgsize.x;
			imgcoord.x++;
		}
		coord.y += (float)buffer.size.y / (float)imgsize.y;
		imgcoord.y++;
	}
}

void	blit_buffer(FRAMEBUFFER buffer, void *image)
{
	UINT 		i;
	IMGDATA		img;

	i = 0;
	img = get_image_data(image);
	if (img.size.x == buffer.size.x
	&& img.size.y == buffer.size.y
	&& img.bpp == buffer.bpp)
		while (i < buffer.array.length)
		{
			((UCHAR*)img.pixels)[i] = *((UCHAR*)ezarray_get_index(buffer.array, i));
			i++;
		}
	else if (img.bpp == buffer.bpp)
		blit_buffer_scaled(buffer, image);
}

MATERIAL	*mtl_light(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "light")))
		return (mtl);
	mtl = new_material(scene, "light");
	mtl->refraction = 1.f;
	mtl->emitting.power = 1.f;
	mtl->emitting.attenuation = 0.002f;
	mtl->emitting.falloff = 5.f;
	mtl->emitting.color = new_vec3(1, 1, 1);
	mtl->emitting.type = POINT;
	return (mtl);
	(void)engine;
}


void	default_scene(ENGINE *engine, SCENE *scene)
{
	RTPRIMITIVE	*p;
	LIGHT		*l;

	scene->active_camera = new_camera(scene, 90, 0.0001, 1000);
	scene->active_camera->transform = new_rttransform(scene,
		(VEC3){1.5, 0.5, 2.5}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	scene->active_camera->transform->target = new_rttransform(scene,
		(VEC3){0, 0.5, 0}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	p = new_rtprim(scene);
	//p->prim = new_cone(0.5, 2);
	//p->prim = new_cylinder(1, 1);
	p->prim = new_sphere(1);
	p->transform = new_rttransform(scene,
		(VEC3){0, 1, 0}, vec3_normalize((VEC3){1, 1, 0}), (VEC3){1, 1, 1});
	//p->material = mtl_rock_waterworn(engine, scene);
	p->material = mtl_rock_copper(engine, scene);
	//p->material = mtl_scuffed_plastic_red(engine, scene);
	//p->material = mtl_stained_glass(engine, scene);

	p = new_rtprim(scene);
	p->prim = new_plane();
	p->transform = new_rttransform(scene,
		(VEC3){0, 0.2, 0}, vec3_normalize((VEC3){0, 1, 0}), (VEC3){1, 1, 1});
	//p->material = mtl_rock_sliced(engine, scene);
	//p->material = mtl_harshbricks(engine, scene);
	p->material = mtl_water(engine, scene);

	p = new_rtprim(scene);
	p->prim = new_plane();
	p->transform = new_rttransform(scene,
		(VEC3){0, 0, 0}, vec3_normalize((VEC3){0, 1, 0}), (VEC3){1, 1, 1});
	//p->material = mtl_rock_sliced(engine, scene);
	//p->material = mtl_harshbricks(engine, scene);
	p->material = mtl_rock_waterworn(engine, scene);

	l = new_light(scene, DIRECTIONAL, (VEC3){200, 200, -200});
	l->power = 0.5f;
	l->color = (VEC3){1, 1, 1};
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->attenuation = 0.002;
	l->falloff = 150;
	l->spot_size = 80;
	//l = new_light(scene, POINT, (VEC3){1.5, 1.5, 1.5});
	l = new_light(scene, POINT, (VEC3){1.5, 1.5, 1.5});
	//l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	l->color = (VEC3){1, 1, 1};
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->power = 2.f;
	l->attenuation = 0.002;
	l->falloff = 5;
	l->spot_size = 80;
	l->ambient_coef = 0.2f;
	l = new_light(scene, DIRECTIONAL, (VEC3){0, 250, 100});
	l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	l->cast_shadow = false;
	l->direction = (VEC3){0, -1, 0};
	l->power = 1.f;
	l->attenuation = 0.002;
	l->falloff = 500;
	l->spot_size = 80;
	/*scene->active_camera->transform->target = new_rttransform(scene,
		(VEC3){-200, 200, 200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});*/
}

VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution)
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
		bufferptr = get_buffer_value(engine->mtlbuffer, screen_coord);
		*((MATERIAL *)bufferptr) = ret->mtl;
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

BOOL	render_scene(ENGINE *e, SCENE *scene)
{
	t_point2	scoord;
	CAMERA		*cam;
	VEC2		nscoord;
	CAST_RETURN	r;
	VEC3		col;
	BOOL		area_lights;
	FRAMEBUFFER	f;

	if (!(cam = scene->active_camera) || !cam->transform)
		return (false);
	e->active_scene = scene;
	update_rttransform(cam->transform);
	scoord = (t_point2){0, 0};
	f = e->framebuffer;
	cam->m4_view = mat4_mult_mat4(cam->transform->current.transform,
			mat4_perspective(cam->fov, f.size.y / (float)f.size.x, cam->znear, cam->zfar));
	area_lights = scene_contains_area_light(scene);
	while (scoord.y < f.size.y)
	{
		scoord.x = 0;
		while (scoord.x < f.size.x)
		{
			if (e->stop_rendering)
				return (false);
			nscoord = normalize_screen_coord(scoord, f.size);
			cam->ray = new_ray(cam->transform->current.position,
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscoord.x, nscoord.y, -1})));
			col = new_vec3(0, 0, 0);
			vml_memset(&r, 0, sizeof(CAST_RETURN));
			if ((r = cast_ray(e, scene, cam->ray)).intersect.intersects)
			{
				get_ret_mtl(&r);
				if (area_lights && r.mtl.alpha > 0.0001)
					col = vec3_add(col, compute_area_lighting(e, &r));
				col = vec3_add(col, compute_lighting(e, &r));
				col = vec3_add(col, compute_reflection(e, &r, &cam->ray));
				col = vec3_add(col, compute_refraction(e, &r, &cam->ray, 1.f));
			}
			put_pixel_to_buffer(f, scoord, vec3_to_vec4(col, 1));
			fill_buffers(e, scoord, &r);
			if (e->progress_callback)
				e->progress_callback(e, (scoord.x + 1 + (scoord.y + 1) * f.size.y) * 100 / (float)(f.size.y * f.size.y + f.size.x));
			scoord.x++;
		}
		scoord.y++;
	}
	return (true);
}

void	print_progress(ENGINE *engine, float progress)
{
	t_rgba		color;
	t_point2	img_size;
	int			i;
	int			heigth;

	if ((engine->stop_rendering = framework_is_done(engine->framework)))
		return ;
	color = rgba(255, 0, 0, 255);
	get_image_size(engine->loading_screen, &img_size.x, &img_size.y);
	heigth = (5.f / 100.f * img_size.y);
	i = img_size.y / 2 - heigth;
	while (i < (img_size.y / 2) + heigth)
	{
		put_image_pixel(engine->loading_screen, &color,
			(t_point2){img_size.x * progress / 100.f, i});
		i++;
	}
	if (SDL_GetTicks() - engine->last_time >= 100)
	{
		clear_window(engine->window);
		put_image_stretched(engine->window, engine->loading_screen);
		engine->last_time = SDL_GetTicks();
		framework_loop_once(engine->framework);
	}
}

VEC4		blur_sample(ENGINE *engine, t_point2 coord, float intensity)
{
	UCHAR		*color;
	VEC4		vcolor;
	UINT		i;
	VEC2		uv;
	t_point2	size;

	i = 0;
	size = engine->framebuffer.size;
	uv = new_vec2(coord.x / (float)size.x, coord.y / (float)size.y);
	vcolor = new_vec4(0, 0, 0, 0);
	while (i < 32)
	{
		coord = (t_point2){(uv.x + (engine->poisson_disc[i].x * 2 - 1) * intensity) * size.x, (uv.y + (engine->poisson_disc[i].y * 2 - 1) * intensity) * size.y};
		coord = (t_point2){CLAMP(coord.x, 0, size.x - 1), CLAMP(coord.y, 0, size.y - 1)};
		color = get_buffer_value(engine->framebuffer, coord);
		vcolor = vec4_add(vcolor, new_vec4(color[2] / 255.f, color[1] / 255.f, color[0] / 255.f, color[3] / 255.f));
		i++;
	}
	return (vec4_fdiv(vcolor, 32.f));
}

void		gamma_correction(ENGINE *engine, t_point2 coord)
{
	UCHAR		*color;
	VEC4		vcolor;
	float		gamma;

	gamma = 1 / 0.65f;
	color = get_buffer_value(engine->framebuffer, coord);
	vcolor = new_vec4(pow(color[2] / 255.f, gamma), pow(color[1] / 255.f, gamma), pow(color[0] / 255.f, gamma), color[3] / 255.f);
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

void		depth_of_field(ENGINE *engine, t_point2 coord)
{
	VEC4		vcolor;
	float		distance;
	float		center_distance;

	distance = *((float*)get_buffer_value(engine->depthbuffer, coord));
	center_distance = *((float*)get_buffer_value(engine->depthbuffer, (t_point2){engine->depthbuffer.size.x / 2, engine->depthbuffer.size.y / 2}));
	vcolor = blur_sample(engine, coord, CLAMP((fabs(distance - center_distance) - center_distance) / 100.f, 0, 0.0025));
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

int		do_post_treatment(ENGINE *engine, t_callback *callback)
{
	t_point2			coord[2];

	coord[0].x = 0;
	coord[1] = engine->framebuffer.size;
	if (!callback || !callback->function)
		return (false);
	while (coord[0].x < coord[1].x)
	{
		coord[0].y = 0;
		while (coord[0].y < coord[1].y)
		{
			callback->function(callback->arg, coord[0]);
			coord[0].y++;
		}
		coord[0].x++;
	}
	return (true);
}

void		blit_framebuffer(FRAMEBUFFER f1, FRAMEBUFFER f2)
{
	t_point2	coord[2];
	UCHAR		*color;

	coord[0].x = 0;
	coord[1] = f1.size;
	while (coord[0].x < coord[1].x)
	{
		coord[0].y = 0;
		while (coord[0].y < coord[1].y)
		{
			color = get_buffer_value(f1, coord[0]);
			put_pixel_to_buffer(f2, coord[0], new_vec4(color[2] / 255.f, color[1] / 255.f, color[0] / 255.f, color[3] / 255.f));
			coord[0].y++;
		}
		coord[0].x++;
	}
}

int		main(int argc, char *argv[])
{
	ENGINE			engine;
	t_engine_opt	options;
	t_callback		callback;

	options.window_size = options.internal_size = (t_point2){1024, 1024};
	options.max_refr = options.max_refl = 3;
	options.area_sampling = 32;
	engine = new_engine(options);
	callback = new_callback(depth_of_field, &engine);
	ezarray_push(&engine.post_treatments, &callback);
	callback = new_callback(gamma_correction, &engine);
	ezarray_push(&engine.post_treatments, &callback);
	default_scene(&engine, &engine.scene);
	clear_renderer(&engine);
	if (render_scene(&engine, &engine.scene))
	{
		UINT	i = 0;
		while (i < engine.post_treatments.length)
		{
			do_post_treatment(&engine, ezarray_get_index(engine.post_treatments, i));
			blit_framebuffer(engine.finalbuffer, engine.framebuffer);
			i++;
		}
		blit_buffer(engine.finalbuffer, engine.image);
		refresh_window(engine.window);
		framework_loop(engine.framework);
	}
	destroy_framework(engine.framework);
	destroy_engine(&engine);
	return (argv[argc - 1][0]);
}
