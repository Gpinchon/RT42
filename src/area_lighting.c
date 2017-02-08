/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:03:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/08 18:04:12 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_area_lighting(ENGINE *engine, CAST_RETURN *ret)
{
	UINT	i;
	UINT	max;
	VEC3	col;
	RAY		r;
	CAST_RETURN	castret;

	i = 0;
	col = new_vec3(0, 0, 0);
	r.origin = vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, 0.0001f));
	RAY		lray = new_ray(engine->active_scene->active_camera->transform->current.position, new_vec3(0, 1, 0));
	VEC3	ndir = ret->intersect.normal;
	UINT	hits = 0;
	max = engine->area_sampling;
	while (i < max)
	{
		castret = cast_light_ray(engine, engine->active_scene, r);
		if (castret.intersect.intersects && castret.mtl.alpha > 0.0001 && castret.mtl.emitting.power)
		{
			hits++;
			castret.mtl.emitting.position = castret.intersect.position;
			lray.direction = vec3_negate(r.direction);
			col = vec3_add(col, compute_point_color(castret.mtl.emitting, ret->mtl, ret->intersect, lray));
		}
		ndir = new_vec3(frand_a_b(-1, 1), frand_a_b(-1, 1), frand_a_b(-1, 1));
		r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn, ndir));
		i++;
	}
	if (hits)
		return (vec3_fdiv(col, hits));
	else return (col);
}

BOOL	scene_contains_area_light(SCENE *scene)
{
	UINT		i;
	ARRAY		primitives;
	RTPRIMITIVE	p;

	i = 0;
	primitives = scene->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		if (p.material
		&& p.material->emitting.power > 0
		&& (p.material->emitting.color.x > 0
		|| p.material->emitting.color.y > 0
		|| p.material->emitting.color.z > 0))
			return (true);
		i++;
	}
	return (false);
}