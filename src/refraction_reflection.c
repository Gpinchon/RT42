/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_reflection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:50:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/17 02:06:45 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_refraction(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray, float aior)
{
	VEC3		color;
	RAY			ray;
	VEC3		direction;
	CAST_RETURN	refrret;

	if (ret->mtl.alpha >= 1 || engine->refr_iteration >= engine->max_refr)
		return ((VEC3){0, 0, 0});
	engine->refr_iteration++;
	color = (VEC3){0, 0, 0};
	direction = vec3_refract(cur_ray->direction, ret->intersect.normal, ret->mtl.refraction, aior);
	ray = new_ray(vec3_add(ret->intersect.position, vec3_scale(direction, 0.0005)), direction);
	if ((refrret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects)
	{
		color = compute_refraction(engine, &refrret, &ray, ret->mtl.refraction);
		color = vec3_add(color, compute_lighting(engine, &refrret));
		color = vec3_mult(color, ret->mtl.refraction_color);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret->mtl.alpha);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret->mtl.roughness);
	}
	return (color);
}

/*VEC3	compute_reflection(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray)
{
	VEC3		color;
	RAY			ray;
	CAST_RETURN	reflret;
	VEC3		raydir;
	int			i;

	if (engine->refl_iteration >= engine->max_refl)
		return ((VEC3){0, 0, 0});
	engine->refl_iteration++;
	color = (VEC3){0, 0, 0};
	raydir = vec3_reflect(cur_ray->direction, ret->intersect.normal);
	ray = new_ray(vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.0005)), raydir);
	i = 0;
	while (i < 4)
	{
		ray.direction = vec3_normalize(vec3_add(raydir, vec2_to_vec3(vec2_scale(engine->poisson_disc[i], ret->mtl.roughness), 1)));
		if (ret->mtl.roughness < 1 && (reflret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects)
		{
			color = vec3_add(color, compute_reflection(engine, &reflret, &ray));
			color = vec3_add(color, compute_refraction(engine, &reflret, &ray, 1.f));
			engine->refr_iteration = 0;
			color = vec3_add(color, compute_lighting(engine, &reflret));
			color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret->mtl.roughness);
			color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, CLAMP(1 - ret->mtl.metalness, 0.1, 1));
			color = vec3_mult(color, ret->mtl.reflection_color);
		}
		i++;
	}
	return (color);
}*/

VEC3	compute_reflection(ENGINE *engine, CAST_RETURN *ret, RAY *cur_ray)
{
	VEC3		color;
	RAY			ray;
	CAST_RETURN	reflret;

	if (engine->refl_iteration >= engine->max_refl)
		return ((VEC3){0, 0, 0});
	engine->refl_iteration++;
	color = (VEC3){0, 0, 0};
	ray = new_ray(vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.0005)), vec3_reflect(cur_ray->direction, ret->intersect.normal));
	ray.direction = vec3_normalize(vec3_fadd(ray.direction, engine->poisson_disc[CLAMP((int)(ret->mtl.roughness * 63.f), 0, 63)].x * ret->mtl.roughness));
	if ((reflret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects && ret->mtl.roughness < 1)
	{
		color = vec3_add(color, compute_reflection(engine, &reflret, &ray));
		color = vec3_add(color, compute_refraction(engine, &reflret, &ray, 1.f));
		engine->refr_iteration = 0;
		color = vec3_add(color, compute_lighting(engine, &reflret));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret->mtl.roughness);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, CLAMP(1 - ret->mtl.metalness, 0.1, 1));
		//color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, 1 - ret->mtl.alpha);
		color = vec3_mult(color, ret->mtl.reflection_color);
	}
	return (color);
}