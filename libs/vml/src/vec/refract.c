/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:48:58 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:13:45 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

VEC3	vec3_refract(VEC3 incident, VEC3 normal, float ior, float aior)
{
	float	cosi;
	float	eta;
	float	k;

	cosi = CLAMP(vec3_dot(normal, incident), -1, 1);
	if (cosi > 0)
	{
		eta = ior / aior;
		normal = vec3_negate(normal);
	}
	else
	{
		eta = aior / ior;
		cosi = -cosi;
	}
	k = 1.f - eta * eta * (1.f - cosi * cosi);
	return (k < 0 ?
		(VEC3){0, 0, 0} :
		vec3_add(vec3_scale(incident, eta),
			vec3_scale(normal, (eta * cosi - sqrtf(k)))));
}

float	refraction_medium(VEC3 incident, VEC3 normal, float ior, float aior)
{
	float	cosi;
	float	eta;

	cosi = CLAMP(vec3_dot(normal, incident), -1, 1);
	if (cosi > 0)
	{
		eta = ior / aior;
		normal = vec3_negate(normal);
	}
	else
	{
		eta = aior / ior;
		cosi = -cosi;
	}
	return (1.f - eta * eta * (1.f - cosi * cosi));
}
