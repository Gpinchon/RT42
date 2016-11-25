/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/25 23:58:05 by gpinchon         ###   ########.fr       */
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

void	default_scene(SCENE *scene)
{
	RTPRIMITIVE	*p;
	p = new_rtprim(scene);
	//p->prim = new_triangle((VEC3){0, 0, 0}, (VEC3){0, -50, 0}, (VEC3){0, 0, -50});
	//p->prim = new_cone(100, 50, (VEC3){0, 0, 100}, (VEC3){0, 0, 0});
	//p->prim = new_cylinder(100, 50, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->prim = new_sphere(100, (VEC3){0, 0, 0});
	//p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, -150}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->base_color = (VEC3){1, 0, 0};
	p->material->roughness = 0;
	p->material->metalness = 1;
	p->material->alpha = 1;
	scene->active_camera = new_camera(scene, 80);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){0, 0, 200}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	scene->active_camera->transform->target = p->transform;
	p = new_rtprim(scene);
	p->prim = new_cylinder(120, 100, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	/*p->prim = new_sphere(100, (VEC3){0, 0, 0});*/
	p->transform = new_transform(scene,
		(VEC3){0, 0, -200}, (VEC3){1, 1, 0}, (VEC3){1, 1, 1});
}

void	update_transform(TRANSFORM *transform)
{
	VEC3	direction;

	if (!transform || transform->updated)
		return ;
	if (transform->target)
	{
		direction = vec3_normalize(vec3_sub(transform->target->position, transform->position));
		transform->rotation = (VEC3){asin(direction.y), -atan2(direction.x, direction.z), transform->rotation.z};
	}
	transform->translate = mat4_translate(transform->position);
	transform->rotate = mat4_rotation(transform->rotation);
	transform->scale = mat4_scale(transform->scaling);
	transform->matrix = mat4_combine(transform->translate, transform->rotate, transform->scale);
	transform->updated = true;
}

INTERSECT	cast_ray(ENGINE *engine, SCENE *scene, t_point2 screen_coord)
{
	UINT		i;
	RTPRIMITIVE	*prim;
	INTERSECT	inter;
	INTERSECT	ret;


	i = 0;
	ret = new_intersect();
	while (i < scene->primitive.length)
	{
		prim = ezarray_get_index(scene->primitive, i);
		if (prim->transform && !prim->transformed)
		{
			update_transform(prim->transform);
			prim->prim.position = mat4_mult_vec3(prim->transform->translate, prim->transform->position);
			prim->prim.direction = mat4_mult_vec3(prim->transform->rotate, vec3_normalize(prim->transform->rotation));
			prim->transformed = true;
		}
		if (engine->inter_functions[prim->prim.type])
		{
			inter = engine->inter_functions[prim->prim.type](prim->prim, scene->active_camera->ray);
			if (!inter.distance[0])
				inter.distance[0] = inter.distance[1];
			if (inter.intersects && (inter.distance[0] < ret.distance[0] || ret.distance[0] == 0))
			{
				ret = inter;
			}
		}
		i++;
	}
	if (ret.intersects)
		put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(ret.normal, 1)));
	return (ret);
}

VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution, float aspect, float fov)
{
	return ((VEC2){
		(2 * ((screen_coord.x + 0.5) / (float)resolution.x) - 1),
		1 - 2 * ((screen_coord.y + 0.5) / (float)resolution.y)});
	(void)fov;
	(void)aspect;
}

void	render_scene(ENGINE *engine)
{
	t_point2	screen_coord;
	CAMERA		*cam;
	VEC2		nscreen_coord;
	float		aspect;
	float		fov;

	cam = engine->scene.active_camera;
	fov = tan(TO_RADIAN(cam->fov) / 2.f);
	aspect = engine->framebuffer.size.y / (float)engine->framebuffer.size.x;
	if (cam && cam->transform)
	{
		update_transform(cam->transform);
	}
	else
		return ;
	screen_coord = (t_point2){0, 0};
	/*cam->m4_view = mat4_perspective(cam->fov, aspect, 0.0001, 1000);
	cam->m4_view = mat4_mult_mat4(cam->m4_view, cam->transform->translate);
	cam->m4_view = mat4_mult_mat4(cam->m4_view, cam->transform->rotate);*/
	//cam->m4_view = cam->transform->matrix;
	cam->m4_view = mat4_mult_mat4(cam->transform->matrix,
			mat4_perspective(cam->fov, aspect, 0.0001, 1000));
	printf("%f, %f, %f\n", cam->transform->position.x, cam->transform->position.y, cam->transform->position.z);
	printf("%f, %f, %f\n", cam->transform->rotation.x, cam->transform->rotation.y, cam->transform->rotation.z);
	while (screen_coord.y < engine->framebuffer.size.y)
	{
		screen_coord.x = 0;
		while (screen_coord.x < engine->framebuffer.size.x)
		{
			nscreen_coord = normalize_screen_coord(screen_coord, engine->framebuffer.size, aspect, fov);
			cam->ray = new_ray(cam->transform->position,
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscreen_coord.x, nscreen_coord.y, -1})));
			cast_ray(engine, &engine->scene, screen_coord);
			/*if ((intersect = cast_ray(engine, &engine->scene)).intersects)
			{
				put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(intersect.normal, 1)));
			}*/
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
