/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:45:23 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 14:02:41 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

t_mat2	mat2_scale(t_vec2 scale)
{
	return ((t_mat2){ .m = {
		scale.x, 0,
		0, scale.y
	}});
}

t_mat3	mat3_scale(t_vec3 scale)
{
	return ((t_mat3){ .m = {
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.x
	}});
}

t_mat4	mat4_scale(t_vec3 scale)
{
	return ((t_mat4){ .m = {
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	}});
}
