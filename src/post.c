/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:04 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/10 11:59:25 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		bloom(ENGINE *engine, t_point2 coord)
{
	VEC4			vcol;
	unsigned char	*col;

	vcol = blur_sample_with_threshold(engine, coord,
	engine->active_scene->bloom_radius, engine->active_scene->bloom_threshold);
	col = get_buffer_value(engine->framebuffer, coord);
	vcol = vec4_add(new_vec4(col[2] / 255.f,
				col[1] / 255.f, col[0] / 255.f, col[3] / 255.f),
			vec4_scale(vcol, engine->active_scene->bloom_intensity));
	put_pixel_to_buffer(engine->finalbuffer, coord, vcol);
}

void		depth_of_field(ENGINE *engine, t_point2 coord)
{
	VEC4		vcol;
	float		dist;
	float		cdist;

	dist = *((float*)get_buffer_value(engine->depthbuffer, coord));
	cdist = *((float*)get_buffer_value(engine->depthbuffer,
				(t_point2){engine->depthbuffer.size.x / 2,
				engine->depthbuffer.size.y / 2}));
	vcol = blur_sample(engine, coord,
			CLAMP((fabs(dist - cdist) - cdist) / 100.f, 0, 0.0025));
	put_pixel_to_buffer(engine->finalbuffer, coord, vcol);
}

BOOL		do_post_treatment(ENGINE *engine, t_callback *callback)
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

void		gamma_correction(ENGINE *engine, t_point2 coord)
{
	VEC4				vcol;
	float				gamma;
	unsigned char		*col;

	gamma = 1 / 0.65f;
	col = get_buffer_value(engine->framebuffer, coord);
	vcol = new_vec4(pow(col[2] / 255.f, gamma), pow(col[1] / 255.f, gamma),
			pow(col[0] / 255.f, gamma), col[3] / 255.f);
	put_pixel_to_buffer(engine->finalbuffer, coord, vcol);
}
