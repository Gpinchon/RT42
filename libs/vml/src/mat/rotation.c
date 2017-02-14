/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:56:16 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/12 14:53:54 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_mat2	mat2_rotation(float angle)
{
	return ((t_mat2){.m = {
		cos(angle), sin(angle),
		-sin(angle), cos(angle)
	}});
}

t_mat3	mat3_rotation(t_vec3 axis)
{
	VEC3	c;
	VEC3	s;

	axis = (VEC3){CLAMP(axis.x < 0 ? axis.x + 6.2831 : axis.x, 0, 6.2831),
				CLAMP(axis.y < 0 ? axis.y + 6.2831 : axis.y, 0, 6.2831),
				CLAMP(axis.z < 0 ? axis.z + 6.2831 : axis.z, 0, 6.2831)};
	c = (VEC3){cos(axis.x), cos(axis.y), cos(axis.z)};
	s = (VEC3){sin(axis.x), sin(axis.y), sin(axis.z)};
	return (mat3_mult_mat3(mat3_mult_mat3(
		(MAT3){.m = {
		1, 0, 0,
		0, c.x, s.x,
		0, -s.x, c.x
		}}, (MAT3){.m = {
		c.y, 0, -s.y,
		0, 1, 0,
		s.y, 0, c.y
		}}), (MAT3){.m = {
		c.z, s.z, 0,
		-s.z, c.z, 0,
		0, 0, 1
	}}));
}

t_mat4	mat4_rotation(t_vec3 axis)
{
	return (mat3_to_mat4(mat3_rotation(axis)));
}
