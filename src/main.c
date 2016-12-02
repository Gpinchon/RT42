/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/02 21:18:16 by gpinchon         ###   ########.fr       */
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
	LIGHT		*l;

	scene->active_camera = new_camera(scene, 80, 0.0001, 1000);
	scene->active_camera->transform = new_transform(scene,
		(VEC3){150, 500, 150}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
	p = new_rtprim(scene);
	p->prim = new_sphere(100, (VEC3){0, 0, 0});
	//p->prim = new_triangle((VEC3){150, 0, 0}, (VEC3){0, 150, 0}, (VEC3){0, 0, 150});
	//p->prim = new_cone(6, 50, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	//p->prim = new_cylinder(100, 50, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	//p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 0}, (VEC3){0, -1, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 2.4175f;
	p->material->base_color = (VEC3){0, 0, 0.5};
	p->material->refraction_color = (VEC3){0, 0, 0.1};
	//p->material->emitting = (VEC3){0, 0, 0.1};
	p->material->roughness = 0;
	p->material->metalness = 1;
	p->material->alpha = 0.2;
	scene->active_camera->transform->target = p->transform;
	p = new_rtprim(scene);
	//p->prim = new_sphere(100, (VEC3){0, 0, 0});
	p->prim = new_cylinder(100, 100, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){250, 0, 0}, (VEC3){1, 1, 1}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 1.f;
	p->material->base_color = (VEC3){0, 1, 0};
	p->material->roughness = 0.5;
	p->material->metalness = 1;
	p->material->alpha = 1;
	p = new_rtprim(scene);
	//p->prim = new_cylinder(100, 500, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	//p->prim = new_cone(6, 50, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, -250}, (VEC3){0, 0, 1}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 1.333f;
	p->material->base_color = (VEC3){0, 0, 1};
	p->material->roughness = 0.2;
	p->material->metalness = 1;
	p->material->alpha = 1;
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){-250, 0, 0}, (VEC3){1, 0, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 2.4175f;
	p->material->base_color = (VEC3){0, 0, 1};
	p->material->roughness = 0.2;
	p->material->metalness = 1;
	p->material->alpha = 1;
	p = new_rtprim(scene);
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, 0, 0}, (VEC3){-0.2, 1, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 2.4175f;
	p->material->base_color = (VEC3){0, 0, 1};
	p->material->roughness = 0.5;
	p->material->metalness = 1;
	p->material->alpha = 0;
	p = new_rtprim(scene);
	p->prim = new_cylinder(50, 0, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){0, -100, -200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->base_color = (VEC3){1, 0, 0};
	p->material->refraction = 1.333f;
	p->material->roughness = 0.5;
	p->material->metalness = 1;
	p->material->alpha = 0;
	/*l = new_light(scene, DIRECTIONAL, (VEC3){200, 200, -200});
	l->cast_shadow = false;
	l->direction = (VEC3){0, -1, 0};
	l->attenuation = 0.002;
	l->falloff = 150;
	l->spot_size = 80;*/
	l = new_light(scene, POINT, (VEC3){-200, 200, 200});
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	//l->power = .5f;
	l->attenuation = 0.002;
	l->falloff = 300;
	l->spot_size = 80;
	/*scene->active_camera->transform->target = new_transform(scene,
		(VEC3){-200, 200, 200}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});*/

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

CAST_RETURN	cast_ray(ENGINE *engine, SCENE *scene, RAY ray)
{
	UINT		i;
	INTERSECT	inter;
	RTPRIMITIVE	*prim;
	CAST_RETURN	ret;

	i = 0;
	vml_memset(&ret, 0, sizeof(CAST_RETURN));
	while (i < scene->primitives.length)
	{
		prim = ezarray_get_index(scene->primitives, i);
		if (prim->transform && !prim->transformed)
		{
			update_transform(prim->transform);
			prim->prim.position = mat4_mult_vec3(prim->transform->translate, prim->transform->position);
			prim->prim.direction = vec3_normalize(mat4_mult_vec3(prim->transform->rotate, prim->transform->rotation));
			/*if (prim->prim.type == plane)
				prim->prim.direction = prim->transform->rotation;*/
			prim->transformed = true;
		}
		if (engine->inter_functions[prim->prim.type])
		{
			inter = engine->inter_functions[prim->prim.type](prim->prim, ray);
			if (inter.intersects && (inter.distance[0] < ret.intersect.distance[0] || ret.intersect.distance[0] == 0))
			{
				ret.intersect = inter;
				ret.rtprimitive = prim;
			}
		}
		i++;
	}
	return (ret);
}

VEC2	normalize_screen_coord(t_point2 screen_coord, t_point2 resolution)
{
	return ((VEC2){
		(2 * ((screen_coord.x + 0.5) / (float)resolution.x) - 1),
		1 - 2 * ((screen_coord.y + 0.5) / (float)resolution.y)});
}

void	fill_buffers(ENGINE *engine, t_point2 screen_coord, CAST_RETURN ret)
{
	void	*bufferptr;

	if (ret.intersect.intersects)
	{
		if (ret.rtprimitive->material)
		{
			put_pixel_to_buffer(engine->framebuffer, screen_coord, vec3_to_vec4(ret.rtprimitive->material->base_color, ret.rtprimitive->material->alpha));
			bufferptr = get_buffer_value(engine->mtlbuffer, screen_coord);
			*((MATERIAL *)bufferptr) = *ret.rtprimitive->material;
		}
		bufferptr = get_buffer_value(engine->positionbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret.intersect.position;
		bufferptr = get_buffer_value(engine->normalbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret.intersect.normal;
		if (RENDER_NORMALS)
			put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(ret.intersect.normal, 1)));
	}
}

VEC3	compute_lighting(ENGINE *engine, CAST_RETURN ret)
{
	UINT		i;
	LIGHT		*lptr;
	VEC3		color;
	RAY			ray;
	CAST_RETURN	lret;

	color = ret.rtprimitive->material->emitting;
	i = 0;
	while (i < engine->active_scene->lights.length)
	{
		lptr = ezarray_get_index(engine->active_scene->lights, i);
		ray.direction = compute_lightdir(*lptr, ret.intersect.position);
		ray.origin = vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.005));
		color = vec3_add(color, compute_point_color(*lptr, *ret.rtprimitive->material, ret.intersect, ray));
		if (lptr->cast_shadow
		&& (lret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects
		&& lret.intersect.distance[0] < vec3_distance(lptr->position, ret.intersect.position))
			color = vec3_sub(color, vec3_scale(color, 0.5));
		i++;
	}
	return (color);
}

VEC3	compute_refraction(ENGINE *engine, CAST_RETURN ret, RAY cur_ray, float aior)
{
	VEC3		color;
	RAY			ray;
	VEC3		direction;
	CAST_RETURN	refrret;

	if (ret.rtprimitive->material->alpha >= 1 || engine->refr_iteration >= MAX_REFR)
		return ((VEC3){0, 0, 0});
	engine->refr_iteration++;
	color = (VEC3){0, 0, 0};
	direction = vec3_refract(cur_ray.direction, ret.intersect.normal, ret.rtprimitive->material->refraction, aior);
	ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(direction, 0.0005)), direction);
	if ((refrret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects)
	{
		color = compute_refraction(engine, refrret, ray, ret.rtprimitive->material->refraction);
		color = vec3_add(color, compute_lighting(engine, refrret));
		color = vec3_add(color, vec3_scale(ret.rtprimitive->material->refraction_color, refraction_medium(cur_ray.direction, ret.intersect.normal, ret.rtprimitive->material->refraction, aior)));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.rtprimitive->material->alpha);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.rtprimitive->material->roughness);
	}
	return (color);
}

VEC3	compute_reflection(ENGINE *engine, CAST_RETURN ret, RAY cur_ray)
{
	VEC3		color;
	RAY			ray;
	CAST_RETURN	reflret;

	if (engine->refl_iteration >= MAX_REFL)
		return ((VEC3){0, 0, 0});
	engine->refl_iteration++;
	color = (VEC3){0, 0, 0};
	ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.0005)), vec3_reflect(cur_ray.direction, ret.intersect.normal));
	if ((reflret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects && ret.rtprimitive->material->roughness < 1)
	{
		color = vec3_add(color, compute_reflection(engine, reflret, ray));
		color = vec3_add(color, compute_refraction(engine, reflret, ray, 1.f));
		engine->refr_iteration = 0;
		color = vec3_add(color, compute_lighting(engine, reflret));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.rtprimitive->material->roughness);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, 1 - ret.rtprimitive->material->alpha);
	}
	return (color);
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
	while (screen_coord.y < engine->framebuffer.size.y)
	{
		screen_coord.x = 0;
		while (screen_coord.x < engine->framebuffer.size.x)
		{
			nscreen_coord = normalize_screen_coord(screen_coord, engine->framebuffer.size);
			cam->ray = new_ray(cam->transform->position,
				mat4_mult_vec3(cam->m4_view, vec3_normalize((VEC3){nscreen_coord.x, nscreen_coord.y, -1})));
			ret = cast_ray(engine, scene, cam->ray);
			if (ret.intersect.intersects)
			{
				col = (VEC3){0, 0, 0};
				fill_buffers(engine, screen_coord, ret);
				col = compute_lighting(engine, ret);
				col = vec3_add(col, compute_reflection(engine, ret, cam->ray));
				engine->refl_iteration = 0;
				col = vec3_add(col, compute_refraction(engine, ret, cam->ray, 1.f));
				engine->refr_iteration = 0;
				put_pixel_to_buffer(engine->framebuffer, screen_coord, vec3_to_vec4(col, 1));
				//put_pixel_to_buffer(engine->framebuffer, screen_coord, vec4_normalize(vec3_to_vec4(vec3_normalize(ret.intersect.position), 1)));
			}
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
	render_scene(&engine, &engine.scene);
	//render_lights(&engine, &engine.scene);
	blit_buffer(engine.framebuffer, engine.image);
	refresh_window(engine.window);
	framework_loop(engine.framework);
	destroy_engine(&engine);
	return (argv[argc - 1][0]);
}
