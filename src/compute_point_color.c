/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_point_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:15:09 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/03 22:07:30 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static float	compute_attenuation(t_light l, VEC3 position)
{
	float	a;

	if (l.type == DIRECTIONAL)
		return (l.power);
	a = 1 / pow(fmax(vec3_distance(l.position, position) - l.falloff, 0)
		/ l.falloff + 1, 2) * l.power;
	return ((a - l.attenuation) / (1 - l.attenuation));
}

VEC3			compute_lightdir(t_light l, VEC3 position)
{
	if (l.type == POINT || l.type == SPOT)
		return (vec3_normalize(vec3_sub(l.position, position)));
	return (vec3_normalize(l.position));
}

VEC3			compute_point_color(LIGHT l, MATERIAL mtl,
	INTERSECT inter, RAY ray)
{
	VEC3	vd;
	VEC3	ld;
	VEC3	c;
	float	a;

	vd = vec3_normalize(vec3_sub(ray.origin, inter.position));
	ld = compute_lightdir(l, inter.position);
	c = mtl.emitting.power ? vec3_scale(mtl.emitting.color, mtl.emitting.power)
		: new_vec3(0, 0, 0);
	a = compute_attenuation(l, inter.position);
	if (l.type == SPOT)
		a *= vec3_dot(vec3_normalize(l.direction), vec3_negate(ld))
		> cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
	if (!a)
		return (c);
	if (mtl.alpha < 1 && vec3_dot(inter.normal, ld) < 0)
		inter.normal = vec3_negate(inter.normal);
	else
		mtl.alpha = 1;
	c = vec3_add(c, vec3_scale(vec3_mult(mtl.base_color, vec3_add(l.color, mtl.base_color)),
		CLAMP(DIFFUSE(inter.normal, vd, ld, &mtl), 0, mtl.alpha)));
	return (vec3_saturate(vec3_scale(vec3_add(c, vec3_scale(vec3_add(l.color, mtl.base_color),
		CLAMP(SPECULAR(inter.normal, vd, ld, &mtl), 0, mtl.alpha))), a)));
}
