/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:54:03 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/05 01:33:00 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_lighting(ENGINE *engine, CAST_RETURN *ret)
{
	UINT		i;
	LIGHT		l;
	VEC3		color;
	VEC3		lcolor;
	RAY			ray;
	CAST_RETURN	lret;

	color = ret->mtl.emitting.color;
	i = 0;
	while (i < engine->active_scene->lights.length)
	{
		l = *((LIGHT*)ezarray_get_index(engine->active_scene->lights, i));
		ray.direction = compute_lightdir(l, ret->intersect.position);
		ray.origin = vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.0001));
		if (l.cast_shadow
		&& (lret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects
		&& lret.intersect.distance[0] < vec3_distance(l.position, ret->intersect.position))
		{
			get_ret_mtl(&lret);
			lcolor = compute_point_color(l, ret->mtl, ret->intersect, ray);
			if (l.ambient_coef)
				color = vec3_add(color, vec3_scale(lcolor, l.ambient_coef));
			if (lret.mtl.alpha < 1)
			{
				color = vec3_add(color, vec3_scale(lcolor, (1 - lret.mtl.alpha) * (1 - l.ambient_coef) * (1 - (lret.intersect.distance[1] - lret.intersect.distance[0]))));
				//color = vec3_add(color, vec3_scale(vec3_add(lcolor, vec3_mult(lret.mtl.base_color, l.color)), (1 - lret.mtl.alpha) * (1 - (lret.intersect.distance[1] - lret.intersect.distance[0]))));
				/*if (!l.ambient_coef)
					color = vec3_add(color, lcolor);*/
				ray.origin = vec3_add(lret.intersect.position, vec3_scale(ray.direction, 0.0001));
				color = vec3_add(color, vec3_scale(lcolor, lret.mtl.alpha));
				while ((lret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects
				&& lret.intersect.distance[0] < vec3_distance(l.position, ret->intersect.position)
				&& lret.mtl.alpha < 1)
				{
					//color = vec3_add(color, compute_point_color(*l, ret->mtl, ret->intersect, ray));
					color = vec3_add(color, vec3_scale(lcolor, (1 - lret.mtl.alpha) * (1 - l.ambient_coef) * (1 - (lret.intersect.distance[1] - lret.intersect.distance[0]))));
					ray.origin = vec3_add(lret.intersect.position, vec3_scale(ray.direction, 0.0001));
				}
			}
		}
		else
			color = vec3_add(color, lcolor = compute_point_color(l, ret->mtl, ret->intersect, ray));
		i++;
	}
	return (vec3_saturate(color));
}
