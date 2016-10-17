/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 16:03:56 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/17 12:11:45 by agadiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3	vec3_normalize(t_vec3 v)
{
	float length;

	if ((length = vec3_length(v)))
	{
		return ((t_vec3){
			v.x /= length,
			v.y /= length,
			v.z /= length
		});
	}
	return (v);
}

t_vec4	vec4_normalize(t_vec4 v)
{
	float length;

	if ((length = vec4_length(v)))
	{
		return ((t_vec4){
			v.x /= length,
			v.y /= length,
			v.z /= length,
			v.w /= length
		});
	}
	return (v);
}
