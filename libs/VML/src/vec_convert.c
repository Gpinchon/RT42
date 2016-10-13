/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:19:22 by gpinchon          #+#    #+#             */
/*   Updated: 2016/10/13 18:17:36 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../VML.h"

t_vec3	vec4_to_vec3(t_vec4 v)
{
	return ((t_vec3){v.x, v.y, v.z});
}

t_vec4	vec3_to_vec4(t_vec3 v)
{
	return((t_vec4){v.x, v.y, v.z, 0});
}

t_vec2	vec3_to_vec2(t_vec3 v)
{
	return ((t_vec2){v.x, v.y});
}

t_vec3	vec2_to_vec3(t_vec2 v)
{
	return((t_vec3){v.x, v.y, 0});
}
