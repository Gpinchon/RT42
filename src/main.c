/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/01 00:23:22 by gpinchon         ###   ########.fr       */
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
		(VEC3){150, 200, 200}, (VEC3){0, 0, 0}, (VEC3){1, 1, 1});
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
	p->material->base_color = (VEC3){0, 0, 0};
	p->material->refraction_color = (VEC3){0, 0, 0.1};
	//p->material->emitting = (VEC3){0, 0, 0.1};
	p->material->roughness = 0;
	p->material->metalness = 1;
	p->material->alpha = 0.1;
	scene->active_camera->transform->target = p->transform;
	p = new_rtprim(scene);
	//p->prim = new_sphere(100, (VEC3){0, 0, 0});
	p->prim = new_cylinder(100, 100, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->transform = new_transform(scene,
		(VEC3){250, 10, 0}, (VEC3){1, 1, 1}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 1.f;
	p->material->base_color = (VEC3){0, 1, 0};
	p->material->roughness = 0.5;
	p->material->metalness = 1;
	p->material->alpha = 1;
	p = new_rtprim(scene);
	//p->prim = new_cone(6, 50, (VEC3){0, 0, 0}, (VEC3){0, 1, 0});
	p->prim = new_plane((VEC3){0, 0, 0}, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, -100, 0}, (VEC3){0, 1, 0}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->refraction = 1.333f;
	p->material->base_color = (VEC3){0, 0, 1};
	p->material->roughness = 0.8;
	p->material->metalness = 1;
	p->material->alpha = 0.5;
	p = new_rtprim(scene);
	p->prim = new_sphere(100, (VEC3){0, 0, 0});
	p->transform = new_transform(scene,
		(VEC3){0, -100, -200}, (VEC3){0, 0, 1}, (VEC3){1, 1, 1});
	p->material = new_material(scene);
	p->material->base_color = (VEC3){1, 0, 0};
	p->material->refraction = 1.333f;
	p->material->roughness = 0.5;
	p->material->metalness = 1;
	p->material->alpha = 0.5;
	/*l = new_light(scene, DIRECTIONAL, (VEC3){1, 1, 1});
	l->direction = (VEC3){0, -1, 0};
	l->power = 0.05;
	l->attenuation = 0.002;
	l->falloff = 150;
	l->spot_size = 80;*/
	l = new_light(scene, POINT, (VEC3){-200, 200, 200});
	l->cast_shadow = true;
	l->direction = (VEC3){0, -1, 0};
	l->attenuation = 0.002;
	l->falloff = 300;
	l->spot_size = 80;

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
			prim->prim.direction = mat4_mult_vec3(prim->transform->rotate, vec3_normalize(prim->transform->rotation));
			prim->transformed = true;
		}
		if (engine->inter_functions[prim->prim.type])
		{
			inter = engine->inter_functions[prim->prim.type](prim->prim, ray);
			if (!inter.distance[0])
				inter.distance[0] = inter.distance[1];
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

VEC3	compute_lighting(ENGINE *engine, SCENE *scene, CAST_RETURN ret)
{
	UINT		i;
	LIGHT		*lptr;
	VEC3		color;
	RAY			ray;
	CAST_RETURN	lret;

	color = ret.rtprimitive->material->emitting;
	i = 0;
	while (i < scene->lights.length)
	{
		lptr = ezarray_get_index(scene->lights, i);
		ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.005)), compute_lightdir(*lptr, ret.intersect.position));
		color = vec3_add(color, vec3_scale(compute_point_color(*lptr, *ret.rtprimitive->material, ret.intersect, ray), ret.rtprimitive->material->alpha));
		if ((lret = cast_ray(engine, scene, ray)).intersect.intersects
		&& lptr->cast_shadow)
			color = vec3_sub(color, vec3_scale(color, 1.f - ret.rtprimitive->material->alpha));
		/*if (!(lret = cast_ray(engine, scene, ray)).intersect.intersects
		|| !lptr->cast_shadow)
			color = vec3_add(color, vec3_scale(compute_point_color(*lptr, *ret.rtprimitive->material, ret.intersect, ray), ret.rtprimitive->material->alpha));
		else
			color = vec3_add(color, vec3_scale(compute_point_color(*lptr, *ret.rtprimitive->material, ret.intersect, ray), 1.f - lret.rtprimitive->material->alpha));*/
		i++;
	}
	return (color);
}

VEC3	vec3_reflect(VEC3 v, VEC3 n)
{
	return (vec3_sub(v, vec3_scale(n, 2 * vec3_dot(v, n))));
}

VEC3	vec3_inverse(VEC3 v)
{
	VEC3	vn;

	vn = vec3_normalize(v);
	return ((VEC3){
		v.x / (vn.x * vn.x),
		v.y / (vn.y * vn.y),
		v.z / (vn.z * vn.z)});
}

VEC3	vec3_refract(VEC3 incident, VEC3 normal, float ior, float aior)
{
	float cosi = CLAMP(vec3_dot(normal, incident), -1, 1); 
	float n1, n2; 
	VEC3 n = normal;
	if (cosi > 0)
	{
		n1 = ior;
		n2 = aior;
		normal = vec3_negate(normal);
	}
	else
	{
		n1 = aior;
		n2 = ior;
		cosi = -cosi;
	} 
	float eta = n1 / n2;
	float k = 1.f - eta * eta * (1.f - cosi * cosi);
	return (k < 0 ?
		(VEC3){0, 0, 0} :
		vec3_add(vec3_scale(incident, eta), vec3_scale(n, (eta * cosi - sqrtf(k)))));
}

float	refraction_medium(VEC3 incident, VEC3 normal, float ior)
{
	float cosi = CLAMP(vec3_dot(incident, normal), -1, 1); 
	float n1, n2; 
	if (cosi > 0)
	{
		n1 = ior;
		n2 = 1.f;
		normal = vec3_negate(normal);
	}
	else
	{
		n1 = 1.f;
		n2 = ior;
		cosi = -cosi;
	} 
	float eta = n1 / n2;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return (k);
}

VEC3	compute_refraction(ENGINE *engine, SCENE *scene, CAST_RETURN ret, RAY cur_ray, float aior)
{
	VEC3		color;
	RAY			ray;
	CAST_RETURN	refrret;

	if (ret.rtprimitive->material->alpha >= 1 || engine->refr_iteration >= 4)
		return ((VEC3){0, 0, 0});
	engine->refr_iteration++;
	color = (VEC3){0, 0, 0};
	VEC3	direction;
	//direction = vec3_normalize(vec3_sub(ret.intersect.position, cur_ray.origin));
	direction = vec3_refract(cur_ray.direction, ret.intersect.normal, ret.rtprimitive->material->refraction, aior);
	//ray = new_ray(vec3_add(position, vec3_scale(cur_ray.direction, 0.0005)), direction);
	ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(direction, 0.0005)), direction);
	if ((refrret = cast_ray(engine, scene, ray)).intersect.intersects)
	{
		color = compute_refraction(engine, scene, refrret, ray, ret.rtprimitive->material->refraction);
		color = vec3_add(color, compute_lighting(engine, scene, refrret));
		color = vec3_add(color, vec3_scale(ret.rtprimitive->material->refraction_color, refraction_medium(cur_ray.direction, ret.intersect.normal, ret.rtprimitive->material->refraction)));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.rtprimitive->material->alpha);
	}
	return (color);
}

VEC3	compute_reflection(ENGINE *engine, SCENE *scene, CAST_RETURN ret, RAY cur_ray)
{
	VEC3		color;
	RAY			ray;
	CAST_RETURN	reflret;

	if (engine->refl_iteration >= 5)
		return ((VEC3){0, 0, 0});
	engine->refl_iteration++;
	color = (VEC3){0, 0, 0};
	ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.0005)), vec3_reflect(cur_ray.direction, ret.intersect.normal));
	if ((reflret = cast_ray(engine, scene, ray)).intersect.intersects && ret.rtprimitive->material->roughness < 1)
	{
		color = vec3_add(color, compute_reflection(engine, scene, reflret, ray));
		color = vec3_add(color, compute_lighting(engine, scene, reflret));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.rtprimitive->material->roughness);
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
				//fill_buffers(engine, screen_coord, ret);
				/*MAT4	finalmat;
				finalmat = mat4_mult_mat4(cam->m4_view, ret.rtprimitive->transform->matrix);
				ret.intersect.position = mat4_mult_vec3(finalmat, ret.intersect.position);*/
				col = compute_lighting(engine, scene, ret);
				col = vec3_add(col, compute_reflection(engine, scene, ret, cam->ray));
				engine->refl_iteration = 0;
				col = vec3_add(col, compute_refraction(engine, scene, ret, cam->ray, 1.f));
				engine->refr_iteration = 0;
				//col = vec3_interp(interp_linear, vec3_add(col, compute_refraction(engine, scene, ret, cam->ray)), col, ret.rtprimitive->material->alpha);
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
