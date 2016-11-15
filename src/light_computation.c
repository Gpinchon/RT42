/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:14:04 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 09:31:33 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	trowbridge_reitz_specular(t_vec3 n, t_vec3 eye, t_vec3 l, float s)
{
	return (pow(1 / (1 + (1 - pow(vec3_dot(n,
		vec3_normalize(vec3_add(l, eye))), 2)) * s), 2));
}

float	blinn_phong_specular(t_vec3 n, t_vec3 eye, t_vec3 l, float s)
{
	return (pow(vec3_dot(vec3_normalize(vec3_add(l, eye)), n), s));
}

float	oren_nayar_diffuse(t_vec3 n, t_vec3 eye, t_vec3 l, t_mtl mtl)
{
	float	ndl;
	float	nde;
	float	lde;
	float	r2;

	ndl = vec3_dot(l, n);
	nde = vec3_dot(n, eye);
	lde = vec3_dot(l, eye) - ndl * nde;
	r2 = mtl.roughness * mtl.roughness;
	return (CLAMP(
		fmax(0.0, ndl) * ((1.0 + r2 * (1 / (r2 + 0.13) + 0.5 / (r2 + 0.33))) +
		(0.45 * r2 / (r2 + 0.09)) *	lde / interp_linear(1.0, fmax(ndl, nde),
		STEP(0.0, lde))) / M_PI, 0, 1)
	);
}

float	lambert_diffuse(t_vec3 n, t_vec3 eye, t_vec3 l, t_mtl mtl)
{
	return (CLAMP(vec3_dot(n, l) + mtl.roughness, 0, 1));
	(void)eye;
}

t_vec3	compute_lightdir(t_light l, t_vec3 position)
{
	if (l.type == POINT || l.type == SPOT)
		return (vec3_normalize(vec3_sub(l.position, position)));
	return (vec3_normalize(l.position));
}