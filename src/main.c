/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 21:21:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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

void	default_scene(SCENE *scene)
{
	RTPRIMITIVE	*p;
	p = new_rtprim(scene);
	p->prim = new_sphere(50, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 0}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->base_color = (VEC3){1, 0, 0};
	p->material->roughness = 0;
	p->material->metalness = 1;
	p->material->alpha = 1;
	scene->active_camera = new_camera(scene);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){10, 10, -100}, (VEC3){0, 0, -1}, (VEC3){1, 1, 1});
	scene->active_camera->transform->target = p->transform;
}

INTERSECT	cast_ray(ENGINE *engine, SCENE *scene)
{
	UINT		i;
	RTPRIMITIVE	*prim;
	INTERSECT	ret;

	i = 0;
	while (i < scene->primitive.length)
	{
		prim = ezarray_get_index(scene->primitive, i);
		if (engine->inter_functions[prim->prim.type]
		&& (ret = engine->inter_functions[prim->prim.type](prim->prim, scene->active_camera->ray)).intersects)
			return (ret);
		i++;
	}
	return (new_intersect());
}

VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution)
{
	return ((VEC2){screen_coord.x / (float)resolution.x, screen_coord.y / (float)resolution.y});
}

#include <stdio.h>

void	render_scene(ENGINE *engine)
{
	t_point2	screen_coord;
	INTERSECT	intersect;
	CAMERA		*cam;
	VEC2		nscreen_coord;
	float		aspect;

	screen_coord = (t_point2){0, 0};
	aspect = engine->framebuffer.size.y / (float)engine->framebuffer.size.x;
	cam = engine->scene.active_camera;
	if (cam && cam->transform && cam->transform->target)
		cam->m4_view = mat4_lookat(cam->transform->position,
		cam->transform->target->position, UPVEC);
	cam->m4_view = mat4_mult_mat4(cam->m4_view,
		mat4_perspective(45, aspect, 0.0001, 1000));
	while (screen_coord.y < engine->framebuffer.size.y)
	{
		screen_coord.x = 0;
		while (screen_coord.x < engine->framebuffer.size.x)
		{
			nscreen_coord = normalize_screen_coord(screen_coord, engine->framebuffer.size);
			/*nscreen_coord = (VEC2){screen_coord.x, screen_coord.y};
			nscreen_coord = (VEC2){2.f * nscreen_coord.x - 1, 2.f * nscreen_coord.y - 1};
			nscreen_coord = (VEC2){(2 * nscreen_coord.x - 1) * aspect, 1 - 2 * nscreen_coord.y};*/
			//put_pixel_to_buffer(engine->framebuffer, screen_coord, (VEC4){1, 0, 0, 1});
			cam->ray = new_ray(
				mat4_mult_vec3(cam->m4_view, cam->transform->position),
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscreen_coord.x, nscreen_coord.y, -1})));
			//printf("%f, %f, %f\n", cam->ray.direction.x, cam->ray.direction.y, cam->ray.direction.z);
			if ((intersect = cast_ray(engine, &engine->scene)).intersects)
				put_pixel_to_buffer(engine->framebuffer, screen_coord, (VEC4){1, 0, 0, 1});
			screen_coord.x++;
		}
		screen_coord.y++;
	}
}

int		main(void)
{
	ENGINE	engine;

	engine = new_engine();
	default_scene(&engine.scene);
	clear_renderer(&engine);
	render_scene(&engine);
	blit_buffer(engine.framebuffer, engine.image);
	refresh_window(engine.window);
	framework_loop(engine.framework);
	destroy_engine(&engine);
	return (0);
}
