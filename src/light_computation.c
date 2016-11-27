/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:14:04 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/27 21:32:21 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 viewdir,
	t_vec3 ldir, float roughness)
{
	float r2 = roughness * roughness;
	float r21 = r2 - 1;
	VEC3	m = vec3_normalize(vec3_add(ldir, viewdir));
	float res = r2 / (M_PI * pow(pow(vec3_dot(normal, m), 2) * r21 + 1, 2));
	return (res);
	/*return (pow(1 / (1 + (1 - pow(vec3_dot(normal,
		vec3_normalize(vec3_add(ldir, viewdir))), 2)) * s), 2));*/
}

float	blinn_phong_specular(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, float s)
{
	if (!s)
		return (0);
	return (pow(vec3_dot(vec3_normalize(vec3_add(ldir, viewdir)), normal), s));
}

float	ggx_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl mtl)
{
	float nv = vec3_dot(normal, viewdir);
	float g = 2 * nv;
	float r2 = mtl.roughness * mtl.roughness;
	float gx = nv + sqrt(r2 + pow((1 - r2) * nv, 2));
	(void)ldir;
	return (g / gx);
}

float	oren_nayar_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 ldir, t_mtl mtl)
{
	/*float	f[7];

	f[0] = vec3_dot(ldir, normal);
	f[1] = vec3_dot(normal, viewdir);
	f[2] = vec3_dot(ldir, viewdir) - f[0] * f[1];
	f[3] = interp_linear(1.0, fmax(f[0], f[1]), STEP(0.0, f[2]));
	f[4] = mtl.roughness * mtl.roughness;
	f[5] = 1.0 + f[4] * (1.0 / (f[4] + 0.13) + 0.5 / (f[4] + 0.33));
	f[6] = 0.45 * f[4] / (f[4] + 0.09);
	return (CLAMP(fmax(0.0, f[0]) * (f[5] + f[6] *
		f[2] / f[3]) / M_PI, 0, 1));*/
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

float	ggx(VEC3 n, VEC3 lv, float roughness)
{
	float r2 = roughness * roughness;
	float nov = vec3_dot(n, lv);
	return (nov + sqrt((nov - nov * r2) * nov + r2));
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
	spec = 0;
	//diff = DIFFUSE(inter.normal, eyedir, ldir, mtl);
	//diff = ggx_diffuse(inter.normal, eyedir, ldir, mtl);
	diff = ggx(inter.normal, ldir, mtl.roughness) * ggx(inter.normal, eyedir, mtl.roughness);
	col = mtl.emitting;
	//col = (VEC3){0, 0, 0};
	if (l.type == SPOT)
		diff *= vec3_dot(vec3_normalize(l.direction), vec3_negate(ldir))
				> cos(TO_RADIAN(l.spot_size / 2.0)) ? 1 : 0;
	if (diff > 0)
	{
		//spec = SPECULAR(inter.normal, eyedir, ldir, mtl.metalness * (1 - mtl.roughness) * 100);
		//spec = SPECULAR(inter.normal, eyedir, ldir, mtl.roughness);
		//spec = ggx(inter.normal, vec3_add(eyedir, ldir), mtl.roughness);
		//printf("roughness : %f, spec %f\n", mtl.roughness, spec);
		att = compute_attenuation(l, inter.position);
		if (att > 0)
		{
			col = vec3_add(col, vec3_scale(vec3_fdiv(vec3_add(l.color, mtl.base_color), 1), diff));
			//col = vec3_add(col, vec3_interp(interp_linear, (VEC3){.03, .03, .03}, col, mtl.metalness));
			col = vec3_scale(col, att);
			if (spec > 0)
				col = vec3_add(col, vec3_scale(l.color, spec));
		}
	}
	return ((VEC3){
		CLAMP(col.x, 0, 1), CLAMP(col.y, 0, 1), CLAMP(col.z, 0, 1)
	});
}
