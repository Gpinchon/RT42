/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 16:03:56 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/11 18:03:55 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_normalize(t_vec2 v)
{
	float length;

	if ((length = 1.f / vec2_length(v)))
	{
		return ((t_vec2){
			v.x *= length,
			v.y *= length
		});
	}
	return (v);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	float length;

	if ((length = 1.f / vec3_length(v)))
	{
		return ((t_vec3){
			v.x *= length,
			v.y *= length,
			v.z *= length
		});
	}
	return (v);
}

t_vec4	vec4_normalize(t_vec4 v)
{
	float length;

	if ((length = 1.f / vec4_length(v)))
	{
		return ((t_vec4){
			v.x *= length,
			v.y *= length,
			v.z *= length,
			v.w *= length
		});
	}
	return (v);
}
