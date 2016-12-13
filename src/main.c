/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 20:02:11 by gpinchon         ###   ########.fr       */
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

void	blit_buffer(FRAMEBUFFER buffer, void *image)
{
	UINT 	i;
	IMGDATA	img;

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
}

void	default_scene(ENGINE *engine, SCENE *scene)
{
	RTPRIMITIVE	*p;
	LIGHT		*l;

	(void)engine;
	scene->active_camera = new_camera(scene, 90, 0.0001, 1000);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){0, 250, 250}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	MATERIAL *mirror = new_material(scene, "mirror");
	mirror->base_color = (VEC3){0.1, 0.1, 0.1};
	mirror->reflection_color = (VEC3){1, 1, 1};
	mirror->refraction = 1.90f;
	mirror->roughness = 0;
	mirror->metalness = 1;
	mirror->alpha = 1;
	p = new_rtprim(scene);
	p->prim = new_sphere(100, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){250, 100, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_scuffed_aluminium(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_sphere(100, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 100, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_scuffed_plastic_red(engine, scene);
	scene->active_camera->transform->target = p->transform;
	p = new_rtprim(scene);
	p->prim = new_sphere(100, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-250, -100, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rock_copper(engine, scene);

	p = new_rtprim(scene);
	p->prim = new_cylinder(100, 500, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){250, 250, -200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rusted_metal(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_cylinder(100, 500, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 250, -200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_greasy_metal(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_cylinder(100, 500, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){-250, 250, -200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_rock_sliced(engine, scene);

	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, -500}, (VEC3){0, 0, 1}, (VEC3){1, 1, 1});
	p->material = mirror;
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 500}, (VEC3){0, 0, -1}, (VEC3){1, 1, 1});
	p->material = mirror;
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){500, 0, 0}, (VEC3){-1, 0, 0}, (VEC3){1, 1, 1});
	p->material = mirror;
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-500, 0, 0}, (VEC3){1, 0, 0}, (VEC3){1, 1, 1});
	p->material = mirror;
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = mtl_water(engine, scene);
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 500, 0}, (VEC3){0, -1, 0}, (VEC3){1, 1, 1});
	p->material = mirror;
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
	l = new_light(scene, POINT, (VEC3){-250, 250, 250});
	//l->color = (VEC3){1, 207.f / 255.f, 197.f / 255.f};
	l->color = (VEC3){1, 1, 1};
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->power = 2.f;
	l->attenuation = 0.002;
	l->falloff = 500;
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

VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution, float fov)
{
	return ((VEC2){
		(2 * ((float)(screen_coord.x + 0.5) / (float)resolution.x) - 1),
		(1 - 2 * ((float)(screen_coord.y + 0.5) / (float)resolution.y))});
	(void)fov;
}

/*VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution, float fov)
{
	if (screen_coord.y == resolution.y - 1)
		printf("%f\n", (1 - (2 * (float)(screen_coord.y + 0.5) / (float)resolution.y)));
	return ((VEC2){
		(2 * ((float)(screen_coord.x + 0.5) / (float)resolution.x) - 1) * TO_RADIAN(fov / 2),
		(1 - (2 * (float)(screen_coord.y + 0.5) / (float)resolution.y)) * TO_RADIAN(fov / 2)});
}*/

void	fill_buffers(ENGINE *engine, t_point2 screen_coord, CAST_RETURN *ret)
{
	void	*bufferptr;

	if (ret->intersect.intersects)
	{
		if (ret->rtprimitive->material)
		{
			put_pixel_to_buffer(engine->framebuffer, screen_coord, vec3_to_vec4(ret->rtprimitive->material->base_color, ret->rtprimitive->material->alpha));
			bufferptr = get_buffer_value(engine->mtlbuffer, screen_coord);
			*((MATERIAL *)bufferptr) = *ret->rtprimitive->material;
		}
		bufferptr = get_buffer_value(engine->positionbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret->intersect.position;
		bufferptr = get_buffer_value(engine->normalbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret->intersect.normal;
		if (RENDER_NORMALS)
			put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(ret->intersect.normal, 1)));
	}
}

void	render_scene(ENGINE *engine, SCENE *scene)
{
	t_point2	screen_coord;
	CAMERA		*cam;
	VEC2		nscreen_coord;
	CAST_RETURN	ret;
	VEC3		col;

	if (!(cam = scene->active_camera) || !cam->transform)
		return ;
	engine->active_scene = scene;
	update_transform(cam->transform);
	screen_coord = (t_point2){0, 0};
	cam->m4_view = mat4_mult_mat4(cam->transform->matrix,
			mat4_perspective(cam->fov, engine->framebuffer.size.y / (float)engine->framebuffer.size.x, cam->znear, cam->zfar));
	//cam->m4_view = cam->transform->matrix;
	while (screen_coord.y < engine->framebuffer.size.y)
	{
		screen_coord.x = 0;
		while (screen_coord.x < engine->framebuffer.size.x)
		{
			nscreen_coord = normalize_screen_coord(screen_coord, engine->framebuffer.size, cam->fov);
			cam->ray = new_ray(cam->transform->position,
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscreen_coord.x, nscreen_coord.y, -1})));
			ret = cast_ray(engine, scene, cam->ray);
			if (ret.intersect.intersects && !RENDER_NORMALS)
			{
				col = (VEC3){0, 0, 0};
				fill_buffers(engine, screen_coord, &ret);
				col = vec3_add(compute_lighting(engine, &ret), compute_reflection(engine, &ret, &cam->ray));
				col = vec3_add(col, compute_refraction(engine, &ret, &cam->ray, 1.f));
				engine->refr_iteration = 0;
				engine->refl_iteration = 0;
				put_pixel_to_buffer(engine->framebuffer, screen_coord, vec3_to_vec4(col, 1));
			}
			else if (ret.intersect.intersects)
				put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(vec3_normalize(ret.intersect.normal), 1)));
			screen_coord.x++;
		}
		screen_coord.y++;
	}
	printf("Done !\n");
}

int		main(int argc, char *argv[])
{
	ENGINE	engine;

	engine = new_engine();
	default_scene(&engine, &engine.scene);
	clear_renderer(&engine);
	render_scene(&engine, &engine.scene);
	blit_buffer(engine.framebuffer, engine.image);
	refresh_window(engine.window);
	framework_loop(engine.framework);
	destroy_engine(&engine);
	return (argv[argc - 1][0]);
}
