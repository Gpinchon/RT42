/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:00:44 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/17 18:01:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC4		blur_sample(ENGINE *engine, t_point2 coord, float intensity)
{
	UCHAR		*color;
	VEC4		vcolor;
	UINT		i;
	VEC2		uv;
	t_point2	size;

	i = 0;
	size = engine->framebuffer.size;
	uv = new_vec2(coord.x / (float)size.x, coord.y / (float)size.y);
	vcolor = new_vec4(0, 0, 0, 0);
	while (i < 32)
	{
		coord = (t_point2){(uv.x + (engine->poisson_disc[i].x * 2 - 1) * intensity) * size.x, (uv.y + (engine->poisson_disc[i].y * 2 - 1) * intensity) * size.y};
		coord = (t_point2){CLAMP(coord.x, 0, size.x - 1), CLAMP(coord.y, 0, size.y - 1)};
		color = get_buffer_value(engine->framebuffer, coord);
		vcolor = vec4_add(vcolor, new_vec4(color[2] / 255.f, color[1] / 255.f, color[0] / 255.f, color[3] / 255.f));
		i++;
	}
	return (vec4_fdiv(vcolor, 32.f));
}

void		gamma_correction(ENGINE *engine, t_point2 coord)
{
	UCHAR		*color;
	VEC4		vcolor;
	float		gamma;

	gamma = 1 / 0.65f;
	color = get_buffer_value(engine->framebuffer, coord);
	vcolor = new_vec4(pow(color[2] / 255.f, gamma), pow(color[1] / 255.f, gamma), pow(color[0] / 255.f, gamma), color[3] / 255.f);
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

void		depth_of_field(ENGINE *engine, t_point2 coord)
{
	VEC4		vcolor;
	float		distance;
	float		center_distance;

	distance = *((float*)get_buffer_value(engine->depthbuffer, coord));
	center_distance = *((float*)get_buffer_value(engine->depthbuffer, (t_point2){engine->depthbuffer.size.x / 2, engine->depthbuffer.size.y / 2}));
	vcolor = blur_sample(engine, coord, CLAMP((fabs(distance - center_distance) - center_distance) / 100.f, 0, 0.0025));
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

BOOL	do_post_treatment(ENGINE *engine, t_callback *callback)
{
	t_point2			coord[2];

	coord[0].x = 0;
	coord[1] = engine->framebuffer.size;
	if (!callback || !callback->function)
		return (false);
	while (coord[0].x < coord[1].x)
	{
		coord[0].y = 0;
		while (coord[0].y < coord[1].y)
		{
			callback->function(callback->arg, coord[0]);
			coord[0].y++;
		}
		coord[0].x++;
	}
	return (true);
}