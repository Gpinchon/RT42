/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/17 20:01:17 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline t_point2	map_uv(t_point2 size, VEC2 uv)
{
	return ((t_point2){
		CLAMP((int)(size.x * uv.x) % size.x, 0, size.x - 1),
		CLAMP((int)(size.y * uv.y) % size.y, 0, size.y - 1)
	});
}

static inline VEC3		map_color_bits(IMGDATA img, t_point2 p)
{
	UCHAR		*pixel;
	VEC3		color;

	color = (VEC3){0, 0, 0};
	pixel = img.pixels + (p.y * img.sizeline + p.x * img.opp);
	if (img.opp > 2)
	{
		color.x = pixel[2] / 255.f;
		color.y = pixel[1] / 255.f;
		color.z = pixel[0] / 255.f;
	}
	else if (img.opp == 1)
	{
		color.x = pixel[0] / 255.f;
		color.y = color.x;
		color.z = color.x;
	}
	return (color);
}

VEC3		sample_texture(void *image, VEC2 uv)
{
	t_point2	tex;
	IMGDATA		img;

	if (!image)
		return ((VEC3){0, 0, 0});
	img = get_image_data(image);
	tex = map_uv(img.size, uv);
	return (map_color_bits(img, tex));
}

VEC3		sample_texture_filtered(void *image, VEC2 uv)
{
	IMGDATA		img;
	VEC3		color;
	float		weight[4];
	t_point2	p[4];
	int			i;

	if (!image)
		return ((VEC3){0, 0, 0});
	color = (VEC3){0, 0, 0};
	img = get_image_data(image);
	p[0] = map_uv(img.size, uv);
	p[3] = (t_point2){CLAMP((p[0].x + 1) % img.size.x, 0, img.size.x),
		CLAMP((p[0].y + 1) % img.size.y, 0, img.size.y)};
	p[1] = (t_point2){p[3].x, p[0].y};
	p[2] = (t_point2){p[0].x, p[3].y};
	uv = (VEC2){fract(uv.x), fract(uv.y)};
	weight[0] = ((1 - uv.x) * (1 - uv.y));
	weight[1] = (uv.x * (1 - uv.y));
	weight[2] = ((1 - uv.x) * uv.y);
	weight[3] = (uv.x *  uv.y);
	i = -1;
	while (++i < 4)
		color = vec3_add(color, vec3_scale(map_color_bits(img, p[i]), weight[i]));
	return (color);
}

VEC2	sample_height_map(void	*height_map, CAST_RETURN *ret)
{
	VEC3	vdir;
	float	ldepth;
	float	cldepth;
	float	cdepth;
	VEC2	dcoord;
	VEC2	ccoord;

	vdir = mat3_mult_vec3(mat3_inverse(ret->tbn), ret->ray.direction);
	cldepth = interp_linear(16, 64, fabs(vdir.z));
	ldepth = 1.0 / cldepth;
	dcoord = vec2_fdiv(vec2_scale(vec3_to_vec2(vdir), ret->mtl.parallax), cldepth);
	cldepth = 0.0;
	ccoord = ret->uv;
	cdepth = 1 - sample_texture_filtered(height_map, ccoord).x;
	while(cldepth < cdepth)
	{
		ccoord = vec2_sub(ccoord, dcoord);
		cdepth = 1 - sample_texture_filtered(height_map, ccoord).x;
		cldepth += ldepth;  
	}
	dcoord = vec2_add(ccoord, dcoord);
	cdepth  = cdepth - cldepth;
	cdepth = cdepth / (cdepth - 1 - sample_texture_filtered(height_map, dcoord).x - cldepth + ldepth);
	return (vec2_add(vec2_scale(dcoord, cdepth), vec2_scale(ccoord, (1.0 - cdepth))));
}

VEC3	sample_normal_map(void *normal_map, CAST_RETURN *ret)
{
	VEC3	tnorm;

	tnorm = sample_texture_filtered(normal_map, ret->uv);
	tnorm = vec3_sub(vec3_scale(tnorm, 2), new_vec3(1, 1, 1));
	tnorm.x *= -1;
	tnorm.y *= -1;
	return (vec3_normalize(mat3_mult_vec3(ret->tbn,
			vec3_normalize(tnorm))));
}
