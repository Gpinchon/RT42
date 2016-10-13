/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecmat_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:19:22 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 17:58:27 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3	vec4_to_vec3(t_vec4 v)
{
	return ((t_vec3){v.x, v.y, v.z});
}

t_vec4	vec3_to_vec4(t_vec3 v)
{
	return((t_vec4){v.x, v.y, v.z, 0});
}

t_mat3	mat4_to_mat3(t_mat4 m)
{
	return((t_mat3){.m = {
		m.m[0], m.m[1], m.m[2],
		m.m[4], m.m[5], m.m[6],
		m.m[8], m.m[9], m.m[10]
	}});
}

t_mat4	mat3_to_mat4(t_mat3 m)
{
	return((t_mat4){.m = {
		m.m[0], m.m[1], m.m[2], 0,
		m.m[4], m.m[5], m.m[6], 0,
		m.m[8], m.m[9], m.m[10], 0,
		0, 0, 0, 1
	}});
}