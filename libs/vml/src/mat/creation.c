/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:55:45 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/12 14:01:30 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_mat3	mat3_translate(t_vec2 translation)
{
	return ((t_mat3){ .m = {
		1, 0, translation.x,
		0, 1, translation.y,
		0, 0, 1,
	}});
}

t_mat4	mat4_translate(t_vec3 translation)
{
	return ((t_mat4){ .m = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translation.x, translation.y, translation.z, 1
	}});
}

t_mat4	mat4_lookat(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_vec3	u;

	target = vec3_normalize(vec3_sub(target, eye));
	up = vec3_normalize(vec3_cross(target, up));
	u = vec3_cross(up, target);
	return ((t_mat4){.m = {
		up.x, u.x, -target.x, 0,
		up.y, u.y, -target.y, 0,
		up.z, u.z, -target.z, 0,
		-vec3_dot(up, eye),
		-vec3_dot(u, eye),
		vec3_dot(target, eye)
	}});
}
