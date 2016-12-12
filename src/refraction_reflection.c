/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_reflection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:50:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/09 00:32:00 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_refraction(ENGINE *engine, CAST_RETURN ret, RAY cur_ray, float aior)
{
	VEC3		color;
	RAY			ray;
	VEC3		direction;
	CAST_RETURN	refrret;

	if (ret.mtl.alpha >= 1 || engine->refr_iteration >= MAX_REFR)
		return ((VEC3){0, 0, 0});
	engine->refr_iteration++;
	color = (VEC3){0, 0, 0};
	direction = vec3_refract(cur_ray.direction, ret.intersect.normal, ret.mtl.refraction, aior);
	ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(direction, 0.0005)), direction);
	if ((refrret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects)
	{
		color = compute_refraction(engine, refrret, ray, ret.mtl.refraction);
		color = vec3_add(color, compute_lighting(engine, refrret));
		//color = vec3_interp(interp_linear, color, ret.mtl.refraction_color, 0.5);
		color = vec3_mult(color, ret.mtl.refraction_color);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.mtl.alpha);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.mtl.roughness);
	}
	return (color);
}

double frand_a_b(double a, double b)
{
	return ((rand()/(double)RAND_MAX) * (b-a) + a);
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
	ray.direction = vec3_normalize(vec3_fadd(ray.direction, frand_a_b(-ret.mtl.roughness, ret.mtl.roughness) * 0.05));
	if ((reflret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects && ret.mtl.roughness < 1)
	{
		color = vec3_add(color, compute_reflection(engine, reflret, ray));
		color = vec3_add(color, compute_refraction(engine, reflret, ray, 1.f));
		engine->refr_iteration = 0;
		color = vec3_add(color, compute_lighting(engine, reflret));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.mtl.roughness);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, CLAMP(1 - ret.mtl.metalness, 0.1, 1));
		//color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, 1 - ret.mtl.alpha);
		color = vec3_mult(color, ret.mtl.reflection_color);
	}
	return (color);
}

/*VEC3	compute_reflection(ENGINE *engine, CAST_RETURN ret, RAY cur_ray)
{
	VEC3		color;
	RAY			ray;
	CAST_RETURN	reflret;

	if (engine->refl_iteration >= MAX_REFL)
		return ((VEC3){0, 0, 0});
	engine->refl_iteration++;
	color = (VEC3){0, 0, 0};
	ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.0005)), vec3_reflect(cur_ray.direction, ret.intersect.normal));
	if ((reflret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects && ret.mtl.roughness < 1)
	{
		color = vec3_add(color, compute_reflection(engine, reflret, ray));
		color = vec3_add(color, compute_refraction(engine, reflret, ray, 1.f));
		engine->refr_iteration = 0;
		color = vec3_add(color, compute_lighting(engine, reflret));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.mtl.roughness);
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, CLAMP(1 - ret.mtl.metalness, 0.03, 1));
		color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, CLAMP(1 - ret.mtl.alpha, 0.03, 1));
		color = vec3_mult(color, ret.mtl.reflection_color);
		//color = vec3_interp(interp_linear, color, ret.mtl.reflection_color, 0.5);
		//color = vec3_add(color, vec3_scale(ret.mtl.reflection_color, 0.5));
	}
	return (vec3_saturate(color));
}*/

/*VEC3	blur_reflection(ENGINE *engine, CAST_RETURN ret, RAY cur_ray)
{
	RAY			ray;
	CAST_RETURN	reflret;
	VEC3		color;
	int			sample;

	color = (VEC3){0, 0, 0};
	sample = 0;
	ray.origin = vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.0005));
	ray.direction = vec3_reflect(cur_ray.direction, ret.intersect.normal);
	VEC3	dir = ray.direction;
	//ray = new_ray(vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 0.0005)), vec3_reflect(cur_ray.direction, ret.intersect.normal));
	while (sample <= 16)
	{
		ray.direction = vec3_fadd(dir, frand_a_b(-ret.mtl.roughness, ret.mtl.roughness) * 0.05);
		if ((reflret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects && ret.mtl.roughness < 1)
		{
			color = vec3_add(color, compute_reflection(engine, reflret, ray));
			color = vec3_add(color, compute_refraction(engine, reflret, ray, 1.f));
			engine->refr_iteration = 0;
			color = vec3_add(color, compute_lighting(engine, reflret));
			color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, ret.mtl.roughness);
			color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, CLAMP(1 - ret.mtl.metalness, 0.03, 1));
			color = vec3_interp(interp_linear, color, (VEC3){0, 0, 0}, 1 - ret.mtl.alpha);
			color = vec3_mult(color, ret.mtl.reflection_color);
		}
		sample++;
	}
	return (vec3_fdiv(color, sample));
}

VEC3	compute_reflection(ENGINE *engine, CAST_RETURN ret, RAY cur_ray)
{
	VEC3		color;

	if (engine->refl_iteration >= MAX_REFL)
		return ((VEC3){0, 0, 0});
	engine->refl_iteration++;
	color = blur_reflection(engine, ret, cur_ray);
	return (color);
}*/