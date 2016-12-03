/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:14:04 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/03 00:59:23 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 viewdir,
	t_vec3 ldir, MATERIAL mtl)
{
	float r2 = mtl.roughness * mtl.roughness;
	float r21 = r2 - 1;
	VEC3	m = vec3_normalize(vec3_negate(vec3_add(ldir, viewdir)));
	float res = r2 / (M_PI * pow(pow(vec3_dot(normal, m), 2) * r21 + 1, 2));
	return (res);
	/*return (pow(1 / (1 + (1 - pow(vec3_dot(normal,
		vec3_normalize(vec3_add(ldir, viewdir))), 2)) * mtl.roughness), 2));*/
}

float	blinn_phong_specular(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl mtl)
{
	float	s;

	s = 100 * mtl.roughness;
	if (!s)
		return (0);
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

float	ggx_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl mtl)
{
	float r2 = mtl.roughness * mtl.roughness;
	float nov = vec3_dot(normal, ldir);
	float g = nov + sqrt((nov - nov * r2) * nov + r2);
	float gx;
	nov = vec3_dot(normal, viewdir);
	gx = nov + sqrt((nov - nov * r2) * nov + r2);
	return (g * gx);
}

float	fresnel_schlick(t_vec3 normal, t_vec3 viewdir, t_vec3 lightdir, t_mtl mtl)
{
	VEC3	half = vec3_normalize(vec3_add(viewdir, lightdir));
	float	f0 = fabs((1.0 - mtl.refraction) / (1.0 + mtl.refraction));
	f0 *= f0;
	return (f0 + (1 - f0) * pow(1 - vec3_dot(viewdir, half), 5));
	(void)normal;
}

float	ggx_distribution(VEC3 normal, VEC3 viewdir, VEC3 lightdir, MATERIAL mtl)
{
	VEC3	half = vec3_normalize(vec3_add(viewdir, lightdir));
	float	NoH = vec3_dot(normal, half);
	float	alpha2 = mtl.roughness * mtl.roughness;
	float	NoH2 = NoH * NoH;
	float	den = NoH2 * alpha2 + (1 - NoH2);
	return ((NoH > 0 ? 1 : 0) * alpha2) / (M_PI * den * den );
}

VEC3	compute_point_color(LIGHT light, MATERIAL mtl,
	INTERSECT inter, RAY ray)
{
	VEC3	viewdir = vec3_normalize(vec3_sub(ray.origin, inter.position));
	VEC3	lightdir = compute_lightdir(light, inter.position);
	VEC3	col;
	float	geom;
	float	spec;
	float	att;

	col = mtl.emitting;
	att = compute_attenuation(light, inter.position);
	if (light.type == SPOT)
		att *= vec3_dot(vec3_normalize(light.direction), vec3_negate(lightdir))
		> cos(TO_RADIAN(light.spot_size / 2.0)) ? 1 : 0;
	geom = CLAMP(ggx_diffuse(inter.normal, viewdir, lightdir, mtl), 0, 1);
	spec = CLAMP(SPECULAR(inter.normal, viewdir, lightdir, mtl) * mtl.metalness, 0, 1);
	col = vec3_add(col, vec3_scale(mtl.base_color, geom));
	col = vec3_add(col, vec3_scale(light.color, spec));
	col = vec3_scale(col, att);
	return (vec3_saturate(col));
}
