/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:05:07 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:04:25 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

VEC3		intersect_compute_position(RAY r, float distance)
{
	return ((VEC3){
		r.origin.x + r.direction.x * distance,
		r.origin.y + r.direction.y * distance,
		r.origin.z + r.direction.z * distance
	});
}

char		intersect_test(float t[2])
{
	return (t[0] > FLOAT_ZERO || t[1] > FLOAT_ZERO);
}

float		find_closest(float t[2])
{
	return (t[0] < t[1] ? t[0] : t[1]);
}

char		solve_quadratic(float a, float b, float c, float *t)
{
	float	discrim;
	float	q;

	discrim = (b * b - 4.f * a * c);
	if (discrim < 0)
		return (0);
	q = -.5f * (b < 0 ? (b - sqrtf(discrim)) : (b + sqrtf(discrim)));
	t[0] = q / a;
	t[1] = c / q;
	if (t[0] > t[1])
	{
		q = t[0];
		t[0] = t[1];
		t[1] = q;
	}
	return (1);
}
