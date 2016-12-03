/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/03 00:28:49 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_point2	map_uv(void *image, VEC2 uv)
{
	IMGDATA		img;
	t_point2	coord;

	img = get_image_data(image);
	coord.x = (int)(img.size.x * uv.x) % img.size.x;
	coord.y = (int)(img.size.y * uv.y) % img.size.y;
	return (coord);
}

VEC3		get_texture_color(void *image, VEC2 uv)
{
	t_point2	tex;
	IMGDATA		img;
	UCHAR	*pixel;
	VEC3	color;

	if (!image)
		return ((VEC3){0, 0, 0});
	tex = map_uv(image, uv);
	img = get_image_data(image);
	pixel = img.pixels + tex.y * img.sizeline + tex.x * img.opp;
	color = (VEC3){pixel[2] / 255.f, pixel[1] / 255.f, pixel[0] / 255.f};
	return (color);
}

/*VEC2		sphere_uv(PRIMITIVE sphere, INTERSECT inter)
{
	VEC2	uv;
	VEC3	nhit;

	nhit = vec3_normalize(vec3_sub(inter.position, sphere.position));
	//uv.x = 0.5 + atan2(nhit.z, nhit.x) / (2.f * M_PI);
	//uv.y = 0.5 - asin(nhit.y) / M_PI;
	uv.x = (1 + atan2(nhit.z, nhit.x) / M_PI) * 0.5;
	uv.y = acosf(nhit.y) / M_PI;
	return (uv);
}*/

VEC2		sphere_uv(PRIMITIVE sphere, INTERSECT inter)
{
	VEC2	uv;
	float	phi;
	VEC3	vp;
	VEC3	vn = UPVEC;
	VEC3	ve = (VEC3){0, 0, 1};

	vp = vec3_normalize(vec3_sub(inter.position, sphere.position));
	phi = acosf(-vec3_dot(vn, vp));
	uv.y = phi / M_PI;
	float theta = (acosf(vec3_dot(vp, ve) / sin(phi))) / (2.f * M_PI);
	if (vec3_dot(vec3_cross(vn, ve), vp) > 0)
		uv.x = theta;
	else
		uv.x = 1 - theta;
	return (uv);
}
