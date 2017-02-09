/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:00:44 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/09 14:57:20 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC4		blur_sample(ENGINE *engine, t_point2 c, float intensity)
{
	UCHAR		*color;
	VEC4		vcolor;
	UINT		i;
	VEC2		uv;
	t_point2	size;

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

/*static inline float		color_to_factor(UCHAR *c)
{
	return ((c[0] + c[1] + c[2]) / 255.f / 3.f);
}*/

VEC4		blur_sample_with_threshold(ENGINE *engine, t_point2 p,
	float intensity, float threshold)
{
	VEC4		c;
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
		c = *((VEC4*)get_buffer_value(engine->hdrbuffer, p));
		if (vec4_dot(c, new_vec4(0.299, 0.587, 0.114, 1)) > threshold)
			vcolor = vec4_add(vcolor, vec4_saturate(c));
		i++;
	}
	return (vec4_fdiv(vcolor, 64));
}

void		gamma_correction(ENGINE *engine, t_point2 coord)
{
	UCHAR		*color;
	VEC4		vcolor;
	float		gamma;

	gamma = 1 / 0.65f;
	color = get_buffer_value(engine->framebuffer, coord);
	vcolor = new_vec4(
		pow(color[2] / 255.f, gamma),
		pow(color[1] / 255.f, gamma),
		pow(color[0] / 255.f, gamma),
		color[3] / 255.f);
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

void		depth_of_field(ENGINE *engine, t_point2 coord)
{
	VEC4		vcolor;
	float		dist;
	float		cdist;

	dist = *((float*)get_buffer_value(engine->depthbuffer, coord));
	cdist = *((float*)get_buffer_value(engine->depthbuffer,
(t_point2){engine->depthbuffer.size.x / 2, engine->depthbuffer.size.y / 2}));
	vcolor = blur_sample(engine, coord, CLAMP((fabs(dist - cdist)
		- cdist) / 100.f, 0, 0.0025));
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

void		bloom(ENGINE *engine, t_point2 coord)
{
	VEC4		vcolor;
	UCHAR		*col;

	vcolor = blur_sample_with_threshold(engine, coord,
		engine->active_scene->bloom_radius,
		engine->active_scene->bloom_threshold);
	col = get_buffer_value(engine->framebuffer, coord);
	vcolor = vec4_add(new_vec4(col[2] / 255.f,
			col[1] / 255.f, col[0] / 255.f, col[3] / 255.f),
		vec4_scale(vcolor, engine->active_scene->bloom_intensity));
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}

float		poisson_ssao(ENGINE *e, t_point2 p)
{
	VEC3		v[3];
	float		f[3];
	t_point2	s;
	VEC2		uv;
	VEC2		*d;
	UINT		i;
	

	i = 0;
	f[1] = 0;
	f[0] = 1.f / *((float*)get_buffer_value(e->depthbuffer, p)) * 0.04;
	s = e->positionbuffer.size;
	v[0] = *((VEC3*)get_buffer_value(e->normalbuffer, p));
	v[1] = *((VEC3*)get_buffer_value(e->positionbuffer, p));
	uv = new_vec2(p.x / (float)s.x, p.y / (float)s.y);
	d = e->poisson_disc;
	while (i < 64)
	{
		p = (P2){CLAMP((uv.x + (d[i].x * 2 - 1) * f[0]) * s.x, 0, s.x - 1),
			CLAMP((uv.y + (d[i].y * 2 - 1) * f[0]) * s.y, 0, s.y - 1)};
		v[2] = vec3_sub(*((VEC3*)get_buffer_value(e->positionbuffer, p)), v[1]);
		f[2] = vec3_dot(v[0], vec3_normalize(v[2]));
		f[1] += f[2] >= 0 ? (f[2] * (2.f / (1.f + vec3_length(v[2])))) : 0;
		i++;
	}
	return (CLAMP(1 - f[1] / 64.f, 0, 1));
}

void		ssao(ENGINE *engine, t_point2 coord)
{
	VEC4		vcolor;
	UCHAR		*col;

	col = get_buffer_value(engine->framebuffer, coord);
	vcolor = vec4_scale(new_vec4(col[2] / 255.f, col[1] / 255.f, col[0] / 255.f, col[3] / 255.f),
		poisson_ssao(engine, coord));
	vcolor.w = 1;
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
