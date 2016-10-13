/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:11:12 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 18:45:43 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3	vec3_mult_vec3(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z,
	});
}

t_vec4	vec4_mult_vec4(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z,
		v1.w * v2.w
	});
}

t_vec3	mat4_mult_vec3(t_mat4 m, t_vec3 v)
{
	return ((t_vec3){
		v.x * m.m[0] + v.y * m.m[4] + v.z * m.m[8] + m.m[12],
		v.x * m.m[1] + v.y * m.m[5] + v.z * m.m[9] + m.m[13],
		v.x * m.m[2] + v.y * m.m[6] + v.z * m.m[10] + m.m[14]
	});
}

t_vec4	mat4_mult_vec4(t_mat4 m, t_vec4 v)
{
	return ((t_vec4){
		m.m[0] * v.x + (v.y * m.m[1] + (v.z * m.m[2] + m.m[3] * v.w)),
		m.m[4] * v.x + (v.y * m.m[5] + (v.z * m.m[6] + m.m[7] * v.w)),
		m.m[8] * v.x + (v.y * m.m[9] + (v.z * m.m[10] + m.m[11] * v.w)),
		m.m[12] * v.x + (v.y * m.m[13] + (v.z * m.m[14] + m.m[15] * v.w))
	});
}
