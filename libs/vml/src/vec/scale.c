/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:59:08 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:25:27 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_scale(t_vec2 v, float f)
{
	return ((t_vec2){v.x * f, v.y * f});
}

t_vec3	vec3_scale(t_vec3 v, float f)
{
	return ((t_vec3){v.x * f, v.y * f, v.z * f});
}

t_vec4	vec4_scale(t_vec4 v, float f)
{
	return ((t_vec4){v.x * f, v.y * f, v.z * f, v.w * f});
}
