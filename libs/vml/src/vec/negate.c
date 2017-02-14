/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:35:34 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:21:11 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_negate(t_vec2 v)
{
	return ((t_vec2){
		-v.x,
		-v.y
	});
}

t_vec3	vec3_negate(t_vec3 v)
{
	return ((t_vec3){
		-v.x,
		-v.y,
		-v.z
	});
}

t_vec4	vec4_negate(t_vec4 v)
{
	return ((t_vec4){
		-v.x,
		-v.y,
		-v.z,
		-v.w
	});
}
