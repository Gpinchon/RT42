/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_formulas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:14:04 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/03 15:42:51 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(VEC3 normal, VEC3 viewdir,
	VEC3 ldir, MATERIAL *mtl)
{
	float	r2;
	float	r21;
	VEC3	m;

	r2 = mtl->roughness * mtl->roughness;
	r21 = r2 - 1;
	m = vec3_normalize((vec3_add(ldir, viewdir)));
	return (r2 / (M_PI * pow(pow(vec3_dot(normal, m), 2) * r21 + 1, 2)));
}

float	blinn_phong_specular(VEC3 normal, VEC3 viewdir,
	VEC3 ldir, MATERIAL *mtl)
{
	float	s;

	s = 100 * mtl->roughness;
	if (!s)
		return (0);
	return (pow(vec3_dot(vec3_normalize(vec3_add(ldir, viewdir)), normal), s));
}

float	oren_nayar_diffuse(VEC3 normal, VEC3 viewdir, VEC3 ldir, t_mtl *mtl)
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
		(0.45 * r2 / (r2 + 0.09)) * lde / interp_linear(1.0, fmax(ndl, nde),
		STEP(0.0, lde))) / M_PI, 0, 1));
}

float	lambert_diffuse(VEC3 normal, VEC3 viewdir, VEC3 ldir, t_mtl *mtl)
{
	return (CLAMP(vec3_dot(normal, ldir), 0, 1));
	(void)mtl;
	(void)viewdir;
}
