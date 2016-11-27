/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:52:48 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/26 21:26:10 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	put_pixel_to_buffer(FRAMEBUFFER buffer, t_point2 coord, VEC4 color)
{
	UCHAR	*index;

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
