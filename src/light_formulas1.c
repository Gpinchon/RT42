/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_formulas1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:17:27 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/18 16:18:22 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline float	f0_term(float r)
{
	return (pow(fabs((1.0 - r) / (1.0 + r)), 2));
}

static inline float	g1v(float dotnv, float k)
{
	return (1.0f / (dotnv * (1.0f - k) + k));
}

float				ggx_specular(VEC3 normal, VEC3 viewdir,
	VEC3 lightdir, MATERIAL *mtl)
{
	float	a[2];
	float	d[2];
	float	f0;
	float	k;
	VEC3	half;

	f0 = f0_term(mtl->refraction);
	a[0] = mtl->roughness * mtl->roughness;
	half = vec3_normalize(vec3_add(viewdir, lightdir));
	d[0] = CLAMP(vec3_dot(normal, lightdir), 0, 1);
	d[1] = CLAMP(vec3_dot(normal, half), 0, 1);
	a[1] = a[0] * a[0];
	k = a[0] / 2.0f;
	return (d[0] * (a[1] / (M_PI * pow(d[1] * d[1] * (a[1] - 1.0) + 1.0f, 2))) *
	(f0 + (1.0 - f0) * (pow(1.0f - CLAMP(vec3_dot(lightdir, half), 0, 1), 5)))
	* g1v(d[0], k) * g1v(CLAMP(vec3_dot(normal, viewdir), 0, 1), k));
}
