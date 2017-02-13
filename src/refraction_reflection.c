/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_reflection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:50:09 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/13 18:53:45 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3	compute_refraction(ENGINE *e, CAST_RETURN *re, RAY *r, float a)
{
	VEC3		c;
	RAY			ray;
	VEC3		d;
	CAST_RETURN	cr;

	if (re->mtl.alpha >= 1 || e->refr_iteration >= e->max_refr)
		return ((VEC3){0, 0, 0});
	e->refr_iteration++;
	c = (VEC3){0, 0, 0};
	d = vec3_refract(r->direction, re->intersect.normal,
		re->mtl.refraction, a);
	ray = new_ray(vec3_add(re->intersect.position,
		vec3_scale(d, 0.0001)), d);
	if ((cr = cast_ray(e, e->active_scene, ray)).intersect.intersects)
	{
		get_ret_mtl(&cr);
		c = vec3_add(c, compute_refraction(e, &cr, &ray, re->mtl.refraction));
		c = vec3_add(c, compute_lighting(e, &cr));
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, re->mtl.alpha);
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, re->mtl.roughness);
		c = vec3_mult(c, re->mtl.refraction_color);
	}
	e->refr_iteration = 0;
	return (c);
}

VEC3	compute_reflection(ENGINE *e, CAST_RETURN *re, RAY *ra)
{
	VEC3		c;
	CAST_RETURN	r;
	float		ro;
	INTERSECT	i;

	if (e->refl_iteration >= e->max_refl)
		return ((VEC3){0, 0, 0});
	e->refl_iteration++;
	c = (VEC3){0, 0, 0};
	ro = re->mtl.roughness;
	i = re->intersect;
	r.ray = new_ray(vec3_add(i.position, vec3_scale(i.normal, 0.0001)),
		vec3_normalize(vec3_fadd(vec3_reflect(ra->direction, i.normal),
		frand_a_b(-ro, ro) * ro)));
	if ((r = cast_ray(e, &e->scene, r.ray)).intersect.intersects && ro < 1)
	{
		get_ret_mtl(&r);
		c = vec3_mult(vec3_add(compute_lighting(e, &r),
		vec3_add(compute_reflection(e, &r, &r.ray),
		compute_refraction(e, &r, &r.ray, 1.f))), re->mtl.reflection_color);
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0},
		(ro + (1 - re->mtl.alpha) + fmax(1 - re->mtl.metalness, 0.2)) / 3.f);
	}
	e->refl_iteration = 0;
	return (c);
}
