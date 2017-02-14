/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fadd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 23:07:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:16:19 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_fadd(t_vec2 v, float d)
{
	return ((t_vec2){
		v.x + d,
		v.y + d
	});
}

t_vec3	vec3_fadd(t_vec3 v, float d)
{
	return ((t_vec3){
		v.x + d,
		v.y + d,
		v.z + d
	});
}

t_vec4	vec4_fadd(t_vec4 v, float d)
{
	return ((t_vec4){
		v.x + d,
		v.y + d,
		v.z + d,
		v.w + d
	});
}
