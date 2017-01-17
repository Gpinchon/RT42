/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:14:04 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/17 19:22:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 viewdir,
	t_vec3 ldir, MATERIAL *mtl)
{
	float r2 = mtl->roughness * mtl->roughness;
	float r21 = r2 - 1;
	VEC3	m = vec3_normalize((vec3_add(ldir, viewdir)));
	float res = r2 / (M_PI * pow(pow(vec3_dot(normal, m), 2) * r21 + 1, 2));
	return (res);
}

float	blinn_phong_specular(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl *mtl)
{
	float	s;

	s = 100 * mtl->roughness;
	if (!s)
		return (0);
	return (pow(vec3_dot(vec3_normalize(vec3_add(ldir, viewdir)), normal), s));
}

float	oren_nayar_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl *mtl)
{
	float	ndl;
	float	nde;
	float	lde;
	float	r2;

	ndl = vec3_dot(ldir, normal);
	nde = vec3_dot(normal, viewdir);
	lde = vec3_dot(ldir, viewdir) - ndl * nde;
	r2 = mtl->roughness * mtl->roughness;
	return (CLAMP(
		fmax(0.0, ndl) * ((1.0 + r2 * (1 / (r2 + 0.13) + 0.5 / (r2 + 0.33))) +
		(0.45 * r2 / (r2 + 0.09)) *	lde / interp_linear(1.0, fmax(ndl, nde),
		STEP(0.0, lde))) / M_PI, 0, 1)
	);
}

float	lambert_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl *mtl)
{
	return (CLAMP(vec3_dot(normal, ldir) + mtl->roughness, 0, 1));
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

static inline float	f0_term(float r)
{
	float	f0 = fabs((1.0 - r) / (1.0 + r));
	f0 *= f0;
	return (f0);
}

static inline float	g1v(float dotnv, float k)
{
	return 1.0f/(dotnv*(1.0f-k)+k);
}

float	ggx_specular(VEC3 normal, VEC3 viewdir, VEC3 lightdir, MATERIAL *mtl)
{
	float	alpha;
	float	alphaSqr;
	float	f0;
	float	dotnl;
	float	dotnh;
	float	k;
	VEC3	half;

	f0 = f0_term(mtl->refraction);
	alpha = mtl->roughness * mtl->roughness;
	half = vec3_normalize(vec3_add(viewdir, lightdir));
	dotnl = CLAMP(vec3_dot(normal, lightdir), 0, 1);
	dotnh = CLAMP(vec3_dot(normal, half), 0, 1);
	alphaSqr = alpha * alpha;
	k = alpha / 2.0f;
	return (dotnl * (alphaSqr / (M_PI * pow(dotnh * dotnh * (alphaSqr - 1.0) + 1.0f, 2))) * (f0 + (1.0 - f0) *
		(pow(1.0f - CLAMP(vec3_dot(lightdir, half), 0, 1), 5))) *
		g1v(dotnl, k) * g1v(CLAMP(vec3_dot(normal, viewdir), 0, 1), k));
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

	if (mtl.emitting.power)
		col = vec3_scale(mtl.emitting.color, mtl.emitting.power);
	else
		col = new_vec3(0, 0, 0);
	att = compute_attenuation(light, inter.position);
	if (light.type == SPOT)
		att *= vec3_dot(vec3_normalize(light.direction), vec3_negate(lightdir))
		> cos(TO_RADIAN(light.spot_size / 2.0)) ? 1 : 0;
	if (!att)
		return (col);
	if (mtl.alpha < 1 && vec3_dot(inter.normal, lightdir) < 0)
		inter.normal = vec3_negate(inter.normal);
	else
		mtl.alpha = 1;
	geom = CLAMP(DIFFUSE(inter.normal, viewdir, lightdir, &mtl), 0, mtl.alpha);
	spec = CLAMP(SPECULAR(inter.normal, viewdir, lightdir, &mtl), 0, mtl.alpha);
	col = vec3_add(col, vec3_mult(light.color, vec3_scale(mtl.base_color, geom)));
	col = vec3_add(col, vec3_scale(light.color, spec));
	return (vec3_saturate(vec3_scale(col, att)));
}
