/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:47:01 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/24 23:15:39 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec3	mat3_mult_vec3(t_mat3 m, t_vec3 v)
{
	return ((t_vec3){
		v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6],
		v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7],
		v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8]
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
