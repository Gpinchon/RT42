/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saturate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:54:08 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/29 17:56:32 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

VEC2	vec2_saturate(VEC2 v)
{
	return ((VEC2){CLAMP(v.x, 0, 1), CLAMP(v.y, 0, 1)});
}

VEC3	vec3_saturate(VEC3 v)
{
	return ((VEC3){CLAMP(v.x, 0, 1), CLAMP(v.y, 0, 1), CLAMP(v.z, 0, 1)});
}

VEC4	vec4_saturate(VEC4 v)
{
	return ((VEC4){
		CLAMP(v.x, 0, 1), CLAMP(v.y, 0, 1),
		CLAMP(v.z, 0, 1), CLAMP(v.w, 0, 1)});
}
