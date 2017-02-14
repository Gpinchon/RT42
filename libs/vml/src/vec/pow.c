/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:57:21 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 13:59:24 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

VEC2	vec2_pow(VEC2 v, float p)
{
	return ((VEC2){
		pow(v.x, p),
		pow(v.y, p)
	});
}

VEC3	vec3_pow(VEC3 v, float p)
{
	return ((VEC3){
		pow(v.x, p),
		pow(v.y, p),
		pow(v.z, p)
	});
}

VEC4	vec4_pow(VEC4 v, float p)
{
	return ((VEC4){
		pow(v.x, p),
		pow(v.y, p),
		pow(v.z, p),
		pow(v.w, p)
	});
}
