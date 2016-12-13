/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:54:03 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 13:01:22 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_lighting(ENGINE *engine, CAST_RETURN *ret)
{
	UINT		i;
	LIGHT		*lptr;
	VEC3		color;
	RAY			ray;
	CAST_RETURN	lret;

	color = ret->mtl.emitting;
	i = 0;
	while (i < engine->active_scene->lights.length)
	{
		lptr = ezarray_get_index(engine->active_scene->lights, i);
		ray.direction = compute_lightdir(*lptr, ret->intersect.position);
		ray.origin = vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.005));
		color = vec3_add(color, compute_point_color(*lptr, ret->mtl, ret->intersect, ray));
		if (lptr->cast_shadow
		&& (lret = cast_ray(engine, engine->active_scene, ray)).intersect.intersects
		&& lret.intersect.distance[0] < vec3_distance(lptr->position, ret->intersect.position))
			color = vec3_sub(color, vec3_scale(color, 0.5));
		i++;
	}
	return (color);
}
