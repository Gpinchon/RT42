/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 19:26:03 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:26:13 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_add(t_vec2 v, t_vec2 v1)
{
	return ((t_vec2){
		v.x + v1.x,
		v.y + v1.y
	});
}

t_vec3	vec3_add(t_vec3 v, t_vec3 v1)
{
	return ((t_vec3){
		v.x + v1.x,
		v.y + v1.y,
		v.z + v1.z
	});
}

t_vec4	vec4_add(t_vec4 v, t_vec4 v1)
{
	return ((t_vec4){
		v.x + v1.x,
		v.y + v1.y,
		v.z + v1.z,
		v.w + v1.w
	});
}
