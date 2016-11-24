/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/24 22:11:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

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

void	default_scene(SCENE *scene)
{
	RTPRIMITIVE	*p;
	p = new_rtprim(scene);
	p->prim = new_sphere(80, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-50, 0, 0}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->base_color = (VEC3){1, 0, 0};
	p->material->roughness = 0;
	p->material->metalness = 1;
	p->material->alpha = 1;
	scene->active_camera = new_camera(scene);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){0, 0, -300}, vec3_normalize((VEC3){0, 0, -1}), (VEC3){1, 1, 1});
	scene->active_camera->transform->target = p->transform;
}

void	update_transform(TRANSFORM *transform)
{
	if (!transform || transform->updated)
		return ;
	if (transform->target)
		transform->rotation = vec3_normalize(vec3_sub(transform->target->position, transform->position));
	transform->matrix = mat4_combine(
		mat4_translate(transform->position),
		mat4_rotation(transform->rotation),
		mat4_scale(transform->scale));
	transform->updated = true;
}

INTERSECT	cast_ray(ENGINE *engine, SCENE *scene)
{
	UINT		i;
	RTPRIMITIVE	*prim;

	i = 0;
	while (i < scene->primitive.length)
	{
		prim = ezarray_get_index(scene->primitive, i);
		if (prim->transform)
		{
			update_transform(prim->transform);
			//prim->prim.position = mat4_mult_vec3(prim->transform->matrix, prim->prim.position);
			prim->prim.position = mat4_mult_vec3(mat4_translate(prim->transform->position), prim->transform->position);
			//mat4_print(prim->transform->matrix);
			//printf("%f, %f, %f\n", prim->prim.position.x, prim->prim.position.y, prim->prim.position.z);
		}
		if (engine->inter_functions[prim->prim.type])
			return (engine->inter_functions[prim->prim.type](prim->prim, scene->active_camera->ray));
		i++;
	}
	return (new_intersect());
}

VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution, float aspect)
{
	return ((VEC2){
		(2 * (screen_coord.x / (float)resolution.x) - 1) * aspect,
		1 - 2 * (screen_coord.y / (float)resolution.y)});
	//return ((VEC2){(float)resolution.x - 2 * screen_coord.x, (float)resolution.y - 2 * screen_coord.y});
}

void	render_scene(ENGINE *engine)
{
	t_point2	screen_coord;
	INTERSECT	intersect;
	CAMERA		*cam;
	VEC2		nscreen_coord;
	float		aspect;

	cam = engine->scene.active_camera;
	if (cam && cam->transform)
		update_transform(cam->transform);
	else
		return ;
	screen_coord = (t_point2){0, 0};
	aspect = engine->framebuffer.size.y / (float)engine->framebuffer.size.x;
	cam->m4_view = mat4_mult_mat4(cam->transform->matrix,
		mat4_perspective(45, aspect, 0.0001, 1000));
	while (screen_coord.y < engine->framebuffer.size.y)
	{
		screen_coord.x = 0;
		while (screen_coord.x < engine->framebuffer.size.x)
		{
			nscreen_coord = normalize_screen_coord(screen_coord, engine->framebuffer.size, aspect);
			cam->ray = new_ray(
				cam->transform->position,
				mat4_mult_vec3(cam->m4_view, (VEC3){nscreen_coord.x, nscreen_coord.y, -1}));
			//printf("%f, %f, %f\n", cam->ray.direction.x, cam->ray.direction.y, cam->ray.direction.z);
			if ((intersect = cast_ray(engine, &engine->scene)).intersects)
			{
				put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(intersect.position, 1)));
				//printf("%f, %f, %f\n", intersect.position.x, intersect.position.y, intersect.position.z);
				//put_pixel_to_buffer(engine->framebuffer, screen_coord, (VEC4){1, 0, 0, 1});
			}
			//put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(intersect.position, 1)));
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
	default_scene(&engine.scene);
	clear_renderer(&engine);
	render_scene(&engine);
	blit_buffer(engine.framebuffer, engine.image);
	refresh_window(engine.window);
	framework_loop(engine.framework);
	destroy_engine(&engine);
	return (argv[argc - 1][0]);
}
