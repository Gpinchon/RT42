/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdiv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 23:12:49 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:17:03 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_fdiv(t_vec2 v, float d)
{
	return ((t_vec2){
		v.x / d,
		v.y / d
	});
}

t_vec3	vec3_fdiv(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x / d,
		v.y / d,
		v.z / d
	});
}

t_vec4	vec4_fdiv(t_vec4 v, float d)
{
	return ((t_vec4){
		v.x / d,
		v.y / d,
		v.z / d,
		v.w / d
	});
}
