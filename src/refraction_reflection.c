/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_reflection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:50:09 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/17 20:40:00 by gpinchon         ###   ########.fr       */
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
	{
		e->refr_iteration = 0;
		return ((VEC3){0, 0, 0});
	}
	e->refr_iteration++;
	c = (VEC3){0, 0, 0};
	d = vec3_refract(r->direction, re->intersect.normal, re->mtl.refraction, a);
	ray = new_ray(vec3_add(re->intersect.position, vec3_scale(d, 0.0005)), d);
	if ((cr = cast_ray(e, e->active_scene, ray)).intersect.intersects)
	{
		get_ret_mtl(&cr);
		c = compute_refraction(e, &cr, &ray, re->mtl.refraction);
		c = vec3_add(c, compute_lighting(e, &cr));
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, re->mtl.alpha);
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, re->mtl.roughness);
		c = vec3_mult(c, re->mtl.refraction_color);
	}
	return (c);
}

VEC3	compute_reflection(ENGINE *e, CAST_RETURN *re, RAY *r)
{
	VEC3		c;
	RAY			ray;
	CAST_RETURN	cr;

	if (e->refl_iteration >= 10)
	{
		e->refl_iteration = 0;
		return ((VEC3){0, 0, 0});
	}
	e->refl_iteration++;
	c = (VEC3){0, 0, 0};
	VEC3	d = vec3_reflect(r->direction, re->intersect.normal);
	ray = new_ray(vec3_add(re->intersect.position, vec3_scale(d, 0.0005)),
		vec3_normalize(vec3_fadd(d,
		(e->poisson_disc[CLAMP((int)(re->mtl.roughness * 63.f), 0, 63)].x * 2 - 1) * re->mtl.roughness)));
	if ((cr = cast_ray(e, e->active_scene, ray)).intersect.intersects && re->mtl.roughness < 1)
	{
		get_ret_mtl(&cr);
		c = vec3_add(c, compute_reflection(e, &cr, &ray));
		c = vec3_add(c, compute_refraction(e, &cr, &ray, 1.f));
		c = vec3_add(c, compute_lighting(e, &cr));
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, re->mtl.roughness);
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, CLAMP(1 - re->mtl.metalness, 0.2, 1));
		c = vec3_mult(c, re->mtl.reflection_color);
	}
	return (c);
}

/*VEC3	compute_reflection(ENGINE *e, CAST_RETURN *re, RAY *r)
{
	VEC3		c;
	RAY			ray;
	CAST_RETURN	cr;


	UINT	i = 0;
	c = (VEC3){0, 0, 0};
	VEC3	d = vec3_reflect(r->direction, re->intersect.normal);
	VEC3	p = vec3_add(re->intersect.position, vec3_scale(d, 0.0005));
	ray = new_ray(p, vec3_normalize(vec3_fadd(d,
			(e->poisson_disc[CLAMP((int)(re->mtl.roughness * 63.f), 0, 63)].x * 2 - 1) * re->mtl.roughness)));
	while (i <= 10
	&& (cr = cast_ray(e, e->active_scene, ray)).intersect.intersects && re->mtl.roughness < 1)
	{
		get_ret_mtl(&cr);
		c = vec3_add(c, compute_refraction(e, &cr, &ray, 1.f));
		c = vec3_add(c, compute_lighting(e, &cr));
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, re->mtl.roughness);
		c = vec3_interp(interp_linear, c, (VEC3){0, 0, 0}, CLAMP(1 - re->mtl.metalness, 0.2, 1));
		c = vec3_mult(c, re->mtl.reflection_color);
		i++;
	}
	return (c);
}*/
