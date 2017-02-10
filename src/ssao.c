/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssao.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:00:44 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 23:40:43 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float		poisson_ssao(ENGINE *e, t_point2 p, UINT i)
{
	VEC3		v[3];
	float		f[3];
	t_point2	s;
	VEC2		uv;
	VEC2		*d;

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
		v[2] = vec3_sub(*((VEC3*)get_buffer_value(e->positionbuffer,p)),
			v[1]);
		f[2] = vec3_dot(v[0], vec3_normalize(v[2]));
		f[1] += f[2] >= 0 ? (f[2] * (2.f / (1.f + vec3_length(v[2])))) : 0;
		i++;
	}
	return (CLAMP(1 - f[1] / 64.f, 0, 1));
}

void		ssao(ENGINE *engine, t_point2 coord)
{
	VEC4			vcolor;
	VEC3			*hdrcol;
	float			ssao_val;
	unsigned char	*col;

	col = get_buffer_value(engine->framebuffer, coord);
	ssao_val = poisson_ssao(engine, coord, 0);
	vcolor = vec4_scale(new_vec4(col[2] / 255.f, col[1] / 255.f,
				col[0] / 255.f, col[3] / 255.f), ssao_val);
	vcolor.w = 1;
	hdrcol = get_buffer_value(engine->hdrbuffer, coord);
	*hdrcol = vec3_scale(*hdrcol, ssao_val);
	put_pixel_to_buffer(engine->finalbuffer, coord, vcolor);
}
