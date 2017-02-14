/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:14:06 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/08 17:55:08 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

FRUSTUM	new_frustum(float left, float right, float bottom, float top)
{
	return ((FRUSTUM){left, right, bottom, top});
}

t_mat4	mat4_perspective(float fov, float aspect, float z_near, float z_far)
{
	float	delta_z;
	float	s;
	float	cotangent;

	fov = TO_RADIAN(fov / 2.f);
	s = sin(fov);
	delta_z = z_far - z_near;
	if (!delta_z || !s || !aspect)
		return (mat4_zero());
	cotangent = cos(fov) / s;
	return ((t_mat4){ .m = {
		cotangent / aspect, 0, 0, 0,
		0, cotangent, 0, 0,
		0, 0, -(z_far + z_near) / delta_z, -1,
		0, 0, -2 * z_near * z_far / delta_z, 0
	}});
}

t_mat4	mat4_orthographic(FRUSTUM frustum, float z_near, float z_far)
{
	t_vec3	t;

	t = (t_vec3){
		-((frustum.y + frustum.x) / (frustum.y - frustum.x)),
		-((frustum.w + frustum.z) / (frustum.w - frustum.z)),
		-((z_far + z_near) / (z_far - z_near))};
	return ((t_mat4){ .m = {
		2 / (frustum.y - frustum.x), 0, 0, 0,
		0, 2 / (frustum.w - frustum.z), 0, 0,
		0, 0, -2 / (z_far - z_near), 0,
		t.x, t.y, t.z, 1
	}});
}
