/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/18 15:42:13 by gpinchon         ###   ########.fr       */
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
	unsigned char	*pixel;
	VEC3			color;

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

VEC3					sample_texture(void *image, VEC2 uv)
{
	t_point2	tex;
	IMGDATA		img;

	if (!image)
		return ((VEC3){0, 0, 0});
	img = get_image_data(image);
	tex = map_uv(img.size, uv);
	return (map_color_bits(img, tex));
}

VEC3					sample_texture_filtered(void *image, VEC2 uv)
{
	IMGDATA		img;
	VEC3		color;
	float		w[4];
	t_point2	p[4];
	int			i;

	if (!image)
		return ((VEC3){0, 0, 0});
	color = (VEC3){0, 0, 0};
	img = get_image_data(image);
	uv.x = fabs(uv.x) * img.size.x;
	uv.y = fabs(uv.y) * img.size.y;
	p[0] = (t_point2){(int)uv.x % img.size.x, (int)uv.y % img.size.y};
	p[3] = (t_point2){(p[0].x + 1) % img.size.x, (p[0].y + 1) % img.size.y};
	p[1] = (t_point2){p[3].x, p[0].y};
	p[2] = (t_point2){p[0].x, p[3].y};
	uv = (VEC2){fract(uv.x), fract(uv.y)};
	w[0] = ((1 - uv.x) * (1 - uv.y));
	w[1] = (uv.x * (1 - uv.y));
	w[2] = ((1 - uv.x) * uv.y);
	w[3] = (uv.x * uv.y);
	i = -1;
	while (++i < 4)
		color = vec3_add(color, vec3_scale(map_color_bits(img, p[i]), w[i]));
	return (color);
}
