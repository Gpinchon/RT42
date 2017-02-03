/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:18:23 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/03 15:47:14 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC2	sample_height_map(void *h, CAST_RETURN *ret)
{
	VEC3	vdir;
	float	d[3];
	VEC2	c[2];
	UINT	tries;

	vdir = mat3_mult_vec3(mat3_inverse(ret->tbn), ret->ray.direction);
	d[1] = interp_linear(64, 128, fabs(vdir.z));
	tries = d[1];
	d[0] = 1.0 / d[1];
	c[1] = vec2_fdiv(vec2_scale(vec3_to_vec2(vdir), ret->mtl.parallax), d[1]);
	d[1] = 0.0;
	c[0] = ret->uv;
	d[2] = 1 - sample_texture(h, c[0]).x;
	while (tries && d[1] < d[2])
	{
		c[0] = vec2_sub(c[0], c[1]);
		d[2] = 1 - sample_texture(h, c[0]).x;
		d[1] += d[0];
		tries--;
	}
	c[1] = vec2_add(c[0], c[1]);
	d[2] = d[2] - d[1];
	d[2] = d[2] /
	(d[2] - 1 - sample_texture(h, c[1]).x - d[1] + d[0]);
	return (vec2_add(vec2_scale(c[1], d[2]), vec2_scale(c[0], (1.0 - d[2]))));
}

VEC3	sample_normal_map(void *normal_map, CAST_RETURN *ret)
{
	VEC3	tnorm;

	tnorm = sample_texture_filtered(normal_map, ret->uv);
	tnorm = vec3_sub(vec3_scale(tnorm, 2), new_vec3(1, 1, 1));
	tnorm.x *= -1;
	tnorm.y *= -1;
	return (vec3_normalize(mat3_mult_vec3(ret->tbn,
			vec3_normalize(tnorm))));
}
