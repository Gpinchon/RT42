/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/03 00:48:37 by gpinchon         ###   ########.fr       */
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
	mtl->emitting.power = 2.f;
	mtl->emitting.attenuation = 0.002f;
	mtl->emitting.falloff = 50.f;
	mtl->emitting.color = new_vec3(1, 1, 1);
	return (mtl);
	(void)engine;
}
void	default_scene(ENGINE *engine, SCENE *scene)
{
	RTPRIMITIVE	*p;
	LIGHT		*l;

	(void)engine;
	scene->active_camera = new_camera(scene, 90, 0.0001, 1000);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){0, 2.5, 2.5}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	scene->active_camera->transform->target = new_transform(scene,
		(VEC3){0, 2.5, -1}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});;
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
	p->transform = new_transform(scene,
		(VEC3){0, 0, -2}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_light(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_cylinder(1, 0, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){-2.50, 0, -2}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rock_sliced(engine, scene);

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
		(VEC3){0, 0, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_octostone(engine, scene);
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
	l = new_light(scene, POINT, (VEC3){0, 2, 1.50});
	//l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	l->color = (VEC3){1, 1, 1};
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->power = 1.f;
	l->attenuation = 0.002;
	l->falloff = 5;
	l->spot_size = 80;
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

VEC3	compute_gi(ENGINE *engine, CAST_RETURN *ret)
{
	UINT	i;
	VEC3	col;
	RAY		r;
	CAST_RETURN	castret;

	i = 0;
	col = new_vec3(0, 0, 0);
	r.origin = vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.005f));
	VEC2	*disc = engine->poisson_disc;
	while (i < 64)
	{
		r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn,
		vec3_normalize(vec3_sub(vec3_scale(
			new_vec3(disc[i].x * 0.5, disc[i].y * 0.5, 1), 2), new_vec3(1, 1, 1)))));
		/*r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn,
		vec3_normalize(vec3_sub(vec3_scale(
			new_vec3(0.5, 0.5, 1), 2), new_vec3(1, 1, 1)))));*/
		//return (r.direction);
		//r.direction = ret->intersect.normal;
		castret = cast_ray(engine, engine->active_scene, r);
		if (castret.intersect.intersects && castret.mtl.alpha > 0.0001 && castret.mtl.emitting.power)
		{
			LIGHT l;
			l.power = castret.mtl.emitting.power;
			l.falloff = castret.mtl.emitting.falloff;
			l.color = castret.mtl.emitting.color;
			l.position = castret.intersect.position;
			col = vec3_add(col, compute_point_color(l, ret->mtl, ret->intersect, new_ray(r.origin, vec3_negate(r.direction))));
		}
		i++;
	}
	//return (col);
	return (vec3_fdiv(col, 64));
}

BOOL	render_scene(ENGINE *engine, SCENE *scene)
{
	t_point2	screen_coord;
	CAMERA		*cam;
	VEC2		nscreen_coord;
	CAST_RETURN	ret;
	VEC3		col;

	if (!(cam = scene->active_camera) || !cam->transform)
		return (false);
	engine->active_scene = scene;
	update_transform(cam->transform);
	screen_coord = (t_point2){0, 0};
	cam->m4_view = mat4_mult_mat4(cam->transform->matrix,
			mat4_perspective(cam->fov, engine->framebuffer.size.y / (float)engine->framebuffer.size.x, cam->znear, cam->zfar));
	while (screen_coord.y < engine->framebuffer.size.y)
	{
		screen_coord.x = 0;
		while (screen_coord.x < engine->framebuffer.size.x)
		{
			if (engine->stop_rendering)
				return (false);
			nscreen_coord = normalize_screen_coord(screen_coord, engine->framebuffer.size);
			cam->ray = new_ray(cam->transform->position,
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscreen_coord.x, nscreen_coord.y, -1})));
			ret = cast_ray(engine, scene, cam->ray);
			col = (VEC3){0, 0, 0};
			if (ret.intersect.intersects && !RENDER_NORMALS)
			{
				fill_buffers(engine, screen_coord, &ret);
				//col = compute_lighting(engine, &ret);
				//col = compute_reflection(engine, &ret, &cam->ray);
				col = vec3_add(compute_lighting(engine, &ret), compute_reflection(engine, &ret, &cam->ray));
				col = vec3_add(col, compute_refraction(engine, &ret, &cam->ray, 1.f));
				engine->refr_iteration = 0;
				engine->refl_iteration = 0;
				if (ret.mtl.alpha > 0.0001)
					col = vec3_add(col, compute_gi(engine, &ret));
				//col = compute_gi(engine, &ret);
			}
			else if (ret.intersect.intersects)
				put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(vec3_normalize(ret.intersect.normal), 1)));
			put_pixel_to_buffer(engine->framebuffer, screen_coord, vec3_to_vec4(col, 1));
			if (engine->progress_callback)
				engine->progress_callback(engine, (screen_coord.x + 1 + (screen_coord.y + 1) * engine->framebuffer.size.y) * 100 / (float)(engine->framebuffer.size.y * engine->framebuffer.size.y + engine->framebuffer.size.x));
			screen_coord.x++;
		}
		screen_coord.y++;
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
