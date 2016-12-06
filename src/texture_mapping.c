/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/06 00:11:14 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_point2	map_uv(void *image, VEC2 uv)
{
	IMGDATA		img;
	t_point2	coord;

	img = get_image_data(image);
	coord.x = CLAMP((int)(img.size.x * uv.x) % img.size.x, 0, img.size.x - 1);
	coord.y = CLAMP((int)(img.size.y * uv.y) % img.size.y, 0, img.size.y - 1);
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

float	color_to_factor(VEC3 color)
{
	return ((color.x + color.y + color.z) / 3.f);
}

VEC2		sphere_uv(PRIMITIVE sphere, INTERSECT inter)
{
	float	phi;
	VEC2	uv;
	VEC3	vp;
	VEC3	vn;
	VEC3	ve;

	if (!sphere.direction.x
	&& !sphere.direction.y
	&& !sphere.direction.z)
		vn = UPVEC;
	else
		vn = sphere.direction;
	ve = vec3_cross(vn, (VEC3){0, 0, 1});
	vp = vec3_normalize(vec3_sub(inter.position, sphere.position));
	phi = acosf(-vec3_dot(vn, vp));
	uv.y = phi / M_PI;
	uv.x = (acosf(vec3_dot(vp, ve) / sin(phi))) / (2.f * M_PI);
	if (vec3_dot(vec3_cross(vn, ve), vp) <= 0)
		uv.x = 1 - uv.x;
	return (uv);
}

VEC2		cylinder_uv(PRIMITIVE cylinder, INTERSECT inter)
{
	VEC2	uv;
	VEC3	vp;
	VEC3	vn;
	VEC3	ve;

	if (!cylinder.direction.x
	&& !cylinder.direction.y
	&& !cylinder.direction.z)
		vn = UPVEC;
	else
		vn = cylinder.direction;
	ve = vec3_cross(vn, (VEC3){0, 0, 1});
	vp = vec3_normalize(vec3_sub(inter.position, cylinder.position));
	uv.x = (acosf(vec3_dot(vp, ve) / sin(acosf(-vec3_dot(vn, vp))))) / (2.f * M_PI);
	if (vec3_dot(vec3_cross(vn, ve), vp) <= 0)
		uv.x = 1 - uv.x;
	uv.y = sqrt(pow(vec3_distance(cylinder.position, inter.position), 2) - cylinder.radius2);
	uv.y /= cylinder.size > 0 ? cylinder.size : 1000.f;
	return (uv);
}

VEC2	plane_uv(PRIMITIVE plane, INTERSECT inter)
{
	VEC2	uv;
	VEC3	uaxis;
	VEC3	vaxis;

	inter.position = new_vec3(
	(inter.position.x < 0 ? plane.position.x - inter.position.x : inter.position.x),
	(inter.position.y < 0 ? plane.position.y - inter.position.y : inter.position.y),
	(inter.position.z < 0 ? plane.position.z - inter.position.z : inter.position.z));
	uaxis = new_vec3(plane.direction.y, plane.direction.z, -plane.direction.x);
	vaxis = vec3_cross(uaxis, plane.direction);
	uv.x = vec3_dot(inter.position, uaxis) / 100.f;
	uv.y = vec3_dot(inter.position, vaxis) / 100.f;
	return (uv);
}
