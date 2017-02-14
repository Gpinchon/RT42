/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:19:22 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/10 23:08:38 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec3	vec4_to_vec3(t_vec4 v)
{
	return ((t_vec3){v.x, v.y, v.z});
}

t_vec4	vec3_to_vec4(t_vec3 v, float w)
{
	return ((t_vec4){v.x, v.y, v.z, w});
}

t_vec2	vec3_to_vec2(t_vec3 v)
{
	return ((t_vec2){v.x, v.y});
}

t_vec3	vec2_to_vec3(t_vec2 v, float z)
{
	return ((t_vec3){v.x, v.y, z});
}
