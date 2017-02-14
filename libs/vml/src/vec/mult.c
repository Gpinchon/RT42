/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:11:12 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:20:19 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_mult(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){
		v1.x * v2.x,
		v1.y * v2.y
	});
}

t_vec3	vec3_mult(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	});
}

t_vec4	vec4_mult(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z,
		v1.w * v2.w
	});
}
