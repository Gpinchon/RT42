/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:54:03 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/07 15:24:36 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline VEC3	semi_transparent_shadow(ENGINE *e,
	CAST_RETURN r, VEC3 lcolor, LIGHT l)
{
	float	final_alpha;

	final_alpha = r.mtl.alpha;
	r.ray.origin = vec3_add(r.intersect.position,
		vec3_scale(r.ray.direction, 0.0001));
	while (final_alpha < 1
	&& (r = cast_ray(e, e->active_scene, r.ray)).intersect.intersects
	&& vec3_dot(compute_lightdir(l, r.intersect.position),
		r.ray.direction) > 0)
	{
		get_ret_mtl(&r);
		lcolor = vec3_mult(lcolor, vec3_scale(r.mtl.base_color,
			1 - r.mtl.alpha));
		final_alpha += r.mtl.alpha;
		r.ray.origin = vec3_add(r.intersect.position,
			vec3_scale(r.ray.direction, 0.0001));
	}
	return (vec3_scale(lcolor, (1 - CLAMP(final_alpha, 0,
		1 - l.ambient_coef))));
}

VEC3	compute_lighting(ENGINE *e, CAST_RETURN *r)
{
	UINT		i;
	LIGHT		l;
	VEC3		c;
	CAST_RETURN	lr;

	c = r->mtl.emitting.color;
	i = 0;
	while (i < e->active_scene->lights.length)
	{
		l = *((LIGHT*)ezarray_get_index(e->active_scene->lights, i));
		lr.ray = new_ray(vec3_add(r->intersect.position,
			vec3_scale(r->intersect.normal, 0.0001)),
			compute_lightdir(l, r->intersect.position));
		if (l.cast_shadow
		&& (lr = cast_ray(e, e->active_scene, lr.ray)).intersect.intersects
		&& lr.intersect.distance[0] < vec3_distance(l.position,
			r->intersect.position))
		{
			get_ret_mtl(&lr);
			if (l.ambient_coef)
				c = vec3_add(c,	vec3_scale(compute_point_color(l, r->mtl,
				r->intersect, lr.ray), l.ambient_coef));
			if (lr.mtl.alpha < 1)
				c = vec3_add(c, semi_transparent_shadow(e, lr,
				compute_point_color(l, r->mtl, r->intersect, lr.ray), l));
		}
		else
			c = vec3_add(c,
				compute_point_color(l, r->mtl, r->intersect, lr.ray));
		i++;
	}
	return (vec3_saturate(c));
}
