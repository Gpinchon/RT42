/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:06:23 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/09 23:24:30 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_vec2	vec2_proj(t_vec2 v, t_vec2 v1)
{
	return (vec2_scale(v1, vec2_dot(v, v1) / vec2_dot(v1, v1)));
}

t_vec3	vec3_proj(t_vec3 v, t_vec3 v1)
{
	return (vec3_scale(v1, vec3_dot(v, v1) / vec3_dot(v1, v1)));
}

t_vec4	vec4_proj(t_vec4 v, t_vec4 v1)
{
	return (vec4_scale(v1, vec4_dot(v, v1) / vec4_dot(v1, v1)));
}
