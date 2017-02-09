/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:52:48 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/09 14:49:58 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	fill_buffers(ENGINE *engine, t_point2 screen_coord,
	CAST_RETURN *ret)
{
	void	*bufferptr;

	if (ret->intersect.intersects)
	{
		bufferptr = get_buffer_value(engine->positionbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret->intersect.position;
		bufferptr = get_buffer_value(engine->normalbuffer, screen_coord);
		*((VEC3 *)bufferptr) = ret->intersect.normal;
		bufferptr = get_buffer_value(engine->depthbuffer, screen_coord);
		*((float *)bufferptr) = ret->intersect.distance[0];
		if (RENDER_NORMALS)
			put_pixel_to_buffer(engine->framebuffer, screen_coord,
				vec4_normalize(vec3_to_vec4(ret->intersect.normal, 1)));
	}
}

void	put_pixel_to_buffer(FRAMEBUFFER buffer, t_point2 coord, VEC4 color)
{
	unsigned char	*index;

	index = ezarray_get_index(buffer.array,
		coord.y * buffer.sizeline +
		coord.x * buffer.opp);
	if (!index)
		return ;
	*(index) = CLAMP(color.z * 255.f, 0.f, 255.f);
	*(index + 1) = CLAMP(color.y * 255.f, 0.f, 255.f);
	*(index + 2) = CLAMP(color.x * 255.f, 0.f, 255.f);
	*(index + 3) = CLAMP(color.w * 255.f, 0.f, 255.f);
}

void	put_value_to_buffer(FRAMEBUFFER buffer, t_point2 coord, float value)
{
	float	*index;

	index = ezarray_get_index(buffer.array,
		coord.y * buffer.sizeline +
		coord.x * buffer.opp);
	*(index) = value;
}

void	*get_buffer_value(FRAMEBUFFER buffer, t_point2 coord)
{
	return (ezarray_get_index(buffer.array,
			coord.y * buffer.sizeline +
			coord.x * buffer.opp));
}
