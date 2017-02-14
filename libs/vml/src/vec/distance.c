/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 15:03:35 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 15:05:13 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

float		vec2_distance(VEC2 v, VEC2 v1)
{
	float	a;
	float	b;

	a = v1.x - v.x;
	b = v1.y - v.y;
	return (sqrt(a * a + b * b));
}

float		vec3_distance(VEC3 v, VEC3 v1)
{
	float	a;
	float	b;
	float	c;

	a = v1.x - v.x;
	b = v1.y - v.y;
	c = v1.z - v.z;
	return (sqrt(a * a + b * b + c * c));
}

float		vec4_distance(VEC4 v, VEC4 v1)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = v1.x - v.x;
	b = v1.y - v.y;
	c = v1.z - v.z;
	d = v1.w - v.w;
	return (sqrt(a * a + b * b + c * c + d * d));
}
