/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/05 19:47:36 by gpinchon         ###   ########.fr       */
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

MATERIAL	*mtl_stained_glass(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "stained_glass")))
		return (mtl);
	mtl = new_material(scene, "stained_glass");
	mtl->base_map = load_image_file(engine->framework, "res/stained_glass/stained_glass_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/stained_glass/stained_glass_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/stained_glass/stained_glass_normal.bmp");
	mtl->height_map = load_image_file(engine->framework, "res/stained_glass/stained_glass_height.bmp");
	//mtl->rough_map = load_image_file(engine->framework, "res/stained_glass/stained_glass_rough.bmp");
	mtl->alpha_map = load_image_file(engine->framework, "res/stained_glass/stained_glass_alpha.bmp");
	mtl->parallax = 0.01;
	mtl->refraction = 1.59f * 2.f;
	mtl->refraction_color = (VEC3){1, 1, 1};
	mtl->uv_scale = (VEC2){1, 1};
	mtl->roughness = 0.03;
	mtl->metalness = 0.5;
	mtl->alpha = 0.05;
	return (mtl);
}

void	default_scene(ENGINE *engine, SCENE *scene)
{
	RTPRIMITIVE	*p;
	LIGHT		*l;

	(void)engine;
	scene->active_camera = new_camera(scene, 90, 0.0001, 1000);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){-0, 1.5, 5.5}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	scene->active_camera->transform->target = new_transform(scene,
		(VEC3){0, 0.5, -1}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});;
	MATERIAL *mirror = new_material(scene, "mirror");
	mirror->base_color = (VEC3){0.1, 0.1, 0.1};
	mirror->reflection_color = (VEC3){1, 1, 1};
	mirror->refraction = 1.90f;
	mirror->roughness = 0;
	mirror->metalness = 1;
	mirror->alpha = 1;
	p = new_rtprim(scene);
	p->prim = new_sphere(1, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){3.75, 1, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_scuffed_aluminium(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_sphere(1, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){1.25, 1, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_scuffed_plastic_red(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_sphere(1, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-1.25, 1, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_stained_glass(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_sphere(0.2, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-1.5, 0.2, 0.5}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_aquamarine(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_sphere(1, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-3.75, 1, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rock_copper(engine, scene);

	p = new_rtprim(scene);
	p->prim = new_cylinder(1, 0, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){2.50, 0, -2}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rusted_metal(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_cylinder(1, 0, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	//p->prim = new_sphere(1, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 2, -2}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_greasy_metal(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_cylinder(1, 0, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){-2.50, 0, -2}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rock_sliced(engine, scene);

	/*p = new_rtprim(scene);
	p->prim = new_cylinder(1, 5, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 3, 2}, (VEC3){1, 0, 0}, (VEC3){1, 1, 1});
	p->material = mtl_light(engine, scene);*/

	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, -3}, (VEC3){0, 0, 1}, (VEC3){1, 1, 1});
	p->material = mtl_harshbricks(engine, scene);
	/*p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 5}, (VEC3){0, 0, -1}, (VEC3){1, 1, 1});
	p->material = mtl_brick(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){5, 0, 0}, (VEC3){-1, 0, 0}, (VEC3){1, 1, 1});
	p->material = mtl_brick(engine, scene);*/
	/*p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-5, 0, 0}, (VEC3){1, 0, 0}, (VEC3){1, 1, 1});
	p->material = mtl_brick(engine, scene);*/
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 1.1}, (VEC3){0, 0, -1}, (VEC3){1, 1, 1});
	p->material = mtl_stained_glass(engine, scene);
	/*p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 500, 0}, (VEC3){0, -1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_brick(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_disc(50, (VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 250, 0}, (VEC3){0, -1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_brick(engine, scene);*/
	/*p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, -50}, (VEC3){0, 0, 1}, (VEC3){1, 1, 1});
	p->material = mtl_water(engine, scene);*/
	/*l = new_light(scene, DIRECTIONAL, (VEC3){200, 200, -200});
	l->cast_shadow = false;
	l->direction = (VEC3){0, -1, 0};
	l->attenuation = 0.002;
	l->falloff = 150;
	l->spot_size = 80;*/
	l = new_light(scene, POINT, (VEC3){0, 2, 2});
	//l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	l->color = (VEC3){1, 1, 1};
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->power = 2.f;
	l->attenuation = 0.002;
	l->falloff = 5;
	l->spot_size = 80;
	l->ambient_coef = 0.5f;
	/*l = new_light(scene, POINT, (VEC3){0, 250, 100});
	l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	l->cast_shadow = false;
	l->direction = (VEC3){0, -1, 0};
	l->power = 1.f;
	l->attenuation = 0.002;
	l->falloff = 500;
	l->spot_size = 80;*/
	/*scene->active_camera->transform->target = new_transform(scene,
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
		put_pixel_to_buffer(engine->framebuffer, screen_coord, vec3_to_vec4(ret->mtl.base_color, ret->mtl.alpha));
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
	//VEC2	*disc = engine->poisson_disc;
	RAY		lray = new_ray(engine->active_scene->active_camera->transform->position, new_vec3(0, 1, 0));
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
		//ndir = new_vec3(disc[i].x * 2.f - 1.f, disc[i].y * 2.f - 1.f, (disc[i].x * 2.f - 1.f) * (disc[i].y * 2.f - 1.f));
		r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn, ndir));
		//r.direction = ndir;
		//ndir = new_vec3(disc[i].x * 2.f - 1.f, disc[i].y * 2.f - 1.f, disc[i].x * disc[i].y * 2.f - 1.f);
		//r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn, ndir));
		i++;
	}
	//return (col);
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
	update_transform(cam->transform);
	scoord = (t_point2){0, 0};
	f = e->framebuffer;
	cam->m4_view = mat4_mult_mat4(cam->transform->matrix,
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
			cam->ray = new_ray(cam->transform->position,
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscoord.x, nscoord.y, -1})));
			if ((r = cast_ray(e, scene, cam->ray)).intersect.intersects)
			{
				col = new_vec3(0, 0, 0);
				get_ret_mtl(&r);
				if (area_lights && r.mtl.alpha > 0.0001)
					col = vec3_add(col, compute_area_lighting(e, &r));
				col = vec3_add(col, compute_lighting(e, &r));
				col = vec3_add(col, compute_reflection(e, &r, &cam->ray));
				col = vec3_add(col, compute_refraction(e, &r, &cam->ray, 1.f));
				e->refr_iteration = 0;
				e->refl_iteration = 0;
				fill_buffers(e, scoord, &r);
			}
			put_pixel_to_buffer(f, scoord, vec3_to_vec4(col, 1));
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

int		do_post_treatment(ENGINE *engine)
{

	return (true);
	(void)engine;
}

int		main(int argc, char *argv[])
{
	ENGINE	engine;

	engine = new_engine();
	engine.progress_callback = print_progress;
	engine.loading_screen = load_image_file(engine.framework, "./res/loading_screen.bmp");
	default_scene(&engine, &engine.scene);
	clear_renderer(&engine);
	if (render_scene(&engine, &engine.scene))
	{
		blit_buffer(engine.framebuffer, engine.image);
		refresh_window(engine.window);
		framework_loop(engine.framework);
	}
	destroy_framework(engine.framework);
	destroy_engine(&engine);
	//destroy_engine(&engine);
	return (argv[argc - 1][0]);
}
