/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:50:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/02 22:50:29 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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