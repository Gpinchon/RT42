/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:03:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/13 17:34:38 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline VEC3	intersect_area_primitive(ENGINE *e, CAST_RETURN *ret,
	RAY r)
{
	CAST_RETURN	lret;
	RAY			lray;

	lret = cast_light_ray(e, e->active_scene, r);
	if (lret.intersect.intersects && lret.mtl.alpha > 0.0001
	&& lret.mtl.emitting.power)
	{
		lret.mtl.emitting.position = lret.intersect.position;
		lray.origin = ret->ray.origin;
		lray.direction = vec3_negate(r.direction);
		return (compute_point_color(lret.mtl.emitting,
			ret->mtl, ret->intersect, lray));
	}
	return (new_vec3(-1, 0, 0));
}

VEC3				compute_area_lighting(ENGINE *engine, CAST_RETURN *ret)
{
	UINT		max;
	VEC3		col;
	VEC3		tcol;
	RAY			r;
	UINT		hits;

	col = new_vec3(0, 0, 0);
	r.origin = vec3_add(ret->intersect.position,
		vec3_scale(ret->intersect.normal, 0.0001f));
	hits = 0;
	max = engine->area_sampling;
	while (--max)
	{
		r.direction = vec3_normalize(mat3_mult_vec3(ret->tbn,
			new_vec3(frand_a_b(-1, 1), frand_a_b(-1, 1), frand_a_b(-1, 1))));
		if ((tcol = intersect_area_primitive(engine, ret, r)).x != -1)
		{
			hits++;
			col = vec3_add(col, tcol);
		}
	}
	return (hits ? vec3_fdiv(col, hits) : col);
}

BOOL				scene_contains_area_light(SCENE *scene)
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
