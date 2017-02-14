/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:52:27 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/02 17:54:22 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

VEC2	vec2_inverse(VEC2 v)
{
	VEC2	vn;

	vn = vec2_normalize(v);
	return ((VEC2){
		v.x / (vn.x * vn.x),
		v.y / (vn.y * vn.y)});
}

VEC3	vec3_inverse(VEC3 v)
{
	VEC3	vn;

	vn = vec3_normalize(v);
	return ((VEC3){
		v.x / (vn.x * vn.x),
		v.y / (vn.y * vn.y),
		v.z / (vn.z * vn.z)});
}

VEC4	vec4_inverse(VEC4 v)
{
	VEC4	vn;

	vn = vec4_normalize(v);
	return ((VEC4){
		v.x / (vn.x * vn.x),
		v.y / (vn.y * vn.y),
		v.z / (vn.z * vn.z),
		v.w / (vn.w * vn.w),
	});
}
