/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:04:06 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:26:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_div(t_vec2 v, t_vec2 v1)
{
	return ((t_vec2){
		v.x / v1.x,
		v.y / v1.y
	});
}

t_vec3	vec3_div(t_vec3 v, t_vec3 v1)
{
	return ((t_vec3){
		v.x / v1.x,
		v.y / v1.y,
		v.z / v1.z
	});
}

t_vec4	vec4_div(t_vec4 v, t_vec4 v1)
{
	return ((t_vec4){
		v.x / v1.x,
		v.y / v1.y,
		v.z / v1.z,
		v.w / v1.w
	});
}
