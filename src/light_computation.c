/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:14:04 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 15:55:52 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 viewdir,
	t_vec3 ldir, float s)
{
	return (pow(1 / (1 + (1 - pow(vec3_dot(normal,
		vec3_normalize(vec3_add(ldir, viewdir))), 2)) * s), 2));
}

float	blinn_phong_specular(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, float s)
{
	return (pow(vec3_dot(vec3_normalize(vec3_add(ldir, viewdir)), normal), s));
}

float	oren_nayar_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl mtl)
{
	float	ndl;
	float	nde;
	float	lde;
	float	r2;

	ndl = vec3_dot(ldir, normal);
	nde = vec3_dot(normal, viewdir);
	lde = vec3_dot(ldir, viewdir) - ndl * nde;
	r2 = mtl.roughness * mtl.roughness;
	return (CLAMP(
		fmax(0.0, ndl) * ((1.0 + r2 * (1 / (r2 + 0.13) + 0.5 / (r2 + 0.33))) +
		(0.45 * r2 / (r2 + 0.09)) *	lde / interp_linear(1.0, fmax(ndl, nde),
		STEP(0.0, lde))) / M_PI, 0, 1)
	);
}

float	lambert_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl mtl)
{
	return (CLAMP(vec3_dot(normal, ldir) + mtl.roughness, 0, 1));
	(void)viewdir;
}

float	compute_attenuation(t_light l, VEC3 position)
{
	float	att;

	if (l.type == DIRECTIONAL)
		return (l.power);
	att = 1 / pow(fmax(vec3_distance(l.position, position) - l.falloff, 0)
		/ l.falloff + 1, 2) * l.power;
	return ((att - l.attenuation) / (1 - l.attenuation));
}

t_vec3	compute_lightdir(t_light l, t_vec3 position)
{
	if (l.type == POINT || l.type == SPOT)
		return (vec3_normalize(vec3_sub(l.position, position)));
	return (vec3_normalize(l.position));
}

VEC3	compute_point_color(LIGHT l, MATERIAL mtl,
	INTERSECT inter, RAY ray)
{
	VEC3	col;
	VEC3	ldir;
	VEC3	eyedir;
	float	diff;
	float	spec;
	float	att;

	eyedir = vec3_normalize(vec3_sub(ray.origin, inter.position));
	ldir = compute_lightdir(l, inter.position);
	diff = DIFFUSE(inter.normal, eyedir, ldir, mtl);
	col = (VEC3){0, 0, 0};
	if (l.type == SPOT)
		diff *= vec3_dot(vec3_normalize(l.direction), vec3_negate(ldir))
				> cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
	if (diff > 0)
	{
		spec = SPECULAR(inter.normal, eyedir, ldir, mtl.metalness * (1 - mtl.roughness));
		att = compute_attenuation(l, inter.position);
		col = vec3_scale(vec3_fdiv(vec3_add(l.color, mtl.base_color), 1), diff);
		if (spec > 0 && att > 0)
			col = vec3_interp(interp_linear, (VEC3){.03, .03, .03}, col, mtl.metalness);
			//col = vec3_add(col, vec3_scale(l.color, spec));
		col = vec3_scale(col, att);
	}
	return ((VEC3){
		CLAMP(col.x, 0, 1), CLAMP(col.y, 0, 1), CLAMP(col.z, 0, 1)
	});
}
