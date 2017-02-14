/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:59:42 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/10 00:36:50 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_mat2	new_mat2(t_vec2 a, t_vec2 b)
{
	return ((t_mat2){.m = {
		a.x, a.y,
		b.x, b.y
	}});
}

t_mat3	new_mat3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return ((t_mat3){.m = {
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	}});
}

t_mat4	new_mat4(t_vec4 a, t_vec4 b, t_vec4 c, t_vec4 d)
{
	return ((t_mat4){.m = {
		a.x, a.y, a.z, a.w,
		b.x, b.y, b.z, b.w,
		c.x, c.y, c.z, c.w,
		d.x, d.y, d.z, d.w
	}});
}
