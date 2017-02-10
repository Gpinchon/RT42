/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:37:24 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/10 22:56:48 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC4		blur_sample(ENGINE *engine, t_point2 c, float intensity)
{
	unsigned char	*color;
	VEC4			vcolor;
	UINT			i;
	VEC2			uv;
	t_point2		size;

	i = 0;
	size = engine->framebuffer.size;
	uv = new_vec2(c.x / (float)size.x, c.y / (float)size.y);
	vcolor = new_vec4(0, 0, 0, 0);
	while (i < 64)
	{
		c = (t_point2){(uv.x + (engine->poisson_disc[i].x * 2 - 1) *
			intensity) * size.x, (uv.y + (engine->poisson_disc[i].y * 2 - 1)
			* intensity) * size.y};
		c = (t_point2){CLAMP(c.x, 0, size.x - 1), CLAMP(c.y, 0, size.y - 1)};
		color = get_buffer_value(engine->framebuffer, c);
		vcolor = vec4_add(vcolor, new_vec4(color[2] / 255.f, color[1] / 255.f,
			color[0] / 255.f, color[3] / 255.f));
		i++;
	}
	return (vec4_fdiv(vcolor, 64.f));
}

VEC4		blur_sample_with_threshold(ENGINE *engine, t_point2 p,
	float intensity, float threshold)
{
	VEC3		c;
	VEC4		vcolor;
	VEC2		uv;
	t_point2	size;
	UINT		i;

	i = 0;
	size = engine->framebuffer.size;
	uv = new_vec2(p.x / (float)size.x, p.y / (float)size.y);
	vcolor = new_vec4(0, 0, 0, 0);
	while (i < 64)
	{
		p = (t_point2){(uv.x + (engine->poisson_disc[i].x * 2 - 1) *
			intensity) * size.x, (uv.y + (engine->poisson_disc[i].y * 2 - 1)
			* intensity) * size.y};
		p = (t_point2){CLAMP(p.x, 0, size.x - 1), CLAMP(p.y, 0, size.y - 1)};
		c = *((VEC3*)get_buffer_value(engine->hdrbuffer, p));
		if (vec3_dot(c, new_vec3(0.2125, 0.7154, 0.0721)) > threshold)
			vcolor = vec4_add(vcolor, vec4_saturate(vec3_to_vec4(c, 1)));
		i++;
	}
	return (vec4_fdiv(vcolor, 64));
}
