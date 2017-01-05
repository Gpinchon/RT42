/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/05 18:52:27 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_point2	map_uv(void *image, VEC2 uv)
{
	IMGDATA		img;

	img = get_image_data(image);
	return ((t_point2){
		CLAMP((int)(img.size.x * uv.x) % img.size.x, 0, img.size.x - 1),
		CLAMP((int)(img.size.y * uv.y) % img.size.y, 0, img.size.y - 1)
	});
}

VEC3		sample_texture(void *image, VEC2 uv)
{
	t_point2	tex;
	IMGDATA		img;
	UCHAR		*pixel;
	VEC3		color;

	if (!image)
		return ((VEC3){0, 0, 0});
	color = (VEC3){0, 0, 0};
	tex = map_uv(image, uv);
	img = get_image_data(image);
	pixel = img.pixels + (tex.y * img.sizeline + tex.x * img.opp);
	if (img.opp > 2)
	{
		color.x = pixel[2] / 255.f;
		color.y = pixel[1] / 255.f;
		color.z = pixel[0] / 255.f;
	}
	else if (img.opp == 1)
	{
		color.x = color.y = color.z = pixel[0] / 255.f;
	}
	return (color);
}

VEC3		sample_texture_filtered(void *image, VEC2 uv)
{
	IMGDATA		img;
	UCHAR		*pixel;
	VEC3		color;

	if (!image)
		return ((VEC3){0, 0, 0});
	color = (VEC3){0, 0, 0};
	img = get_image_data(image);
	float fu = (uv.x) * img.size.x;
	float fv = (uv.y) * img.size.y;
	int	u[4];
	int v[4];
	u[0] = u[2] = CLAMP(((int)fu) % img.size.x, 0, img.size.x - 1);
	v[0] = v[1] = CLAMP(((int)fv) % img.size.y, 0, img.size.y - 1);
	u[1] = u[3] = CLAMP((u[0] + 1) % img.size.x, 0, img.size.x - 1);
	v[2] = v[3] = CLAMP((v[0] + 1) % img.size.y, 0, img.size.y - 1);
	float fracu = fu - floorf( fu );
	float fracv = fv - floorf( fv );
	float weight[4];
	weight[0] = ((1 - fracu) * (1 - fracv));
	weight[1] = (fracu * (1 - fracv));
	weight[2] = ((1 - fracu) * fracv);
	weight[3] = (fracu *  fracv);
	
	int i = 0;
	while (i < 4)
	{
		pixel = img.pixels + (v[i] * img.sizeline + u[i] * img.opp);
		if (img.opp > 2)
		{
			color.x += (pixel[2] / 255.f) * weight[i];
			color.y += (pixel[1] / 255.f) * weight[i];
			color.z += (pixel[0] / 255.f) * weight[i];

		}
		else if (img.opp == 1)
			color.x = color.y = color.z += (pixel[0] / 255.f) * weight[i];
		i++;
	}
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
	uv.x = acosf(CLAMP(vec3_dot(vp, ve) / sin(phi), -1, 1)) / (2.f * M_PI);
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
	cylinder.position = vec3_sub(cylinder.position, vec3_scale(cylinder.direction, cylinder.size ? cylinder.size : 10.f));
	ve = vec3_cross(vn, (VEC3){0, 0, 1});
	vp = vec3_normalize(vec3_sub(inter.position, cylinder.position));
	uv.x = acosf(CLAMP(vec3_dot(vp, ve) / sin(acosf(-vec3_dot(vn, vp))), -1, 1)) / (2.f * M_PI);
	if (vec3_dot(vec3_cross(vn, ve), vp) <= 0)
		uv.x = 1 - uv.x;
	uv.y = sqrt(pow(vec3_distance(cylinder.position, inter.position), 2) - cylinder.radius2) / 10.f;
	return (uv);
}

VEC2	plane_uv(PRIMITIVE plane, INTERSECT inter)
{
	VEC2	uv;
	VEC3	t;
	VEC3	dir;
	float	alpha;
	float 	d;

	t = vec3_cross(inter.normal, new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(inter.normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	VEC3	b = vec3_cross(t, inter.normal);
	d = vec3_distance(inter.position, plane.position);
	dir = vec3_normalize(vec3_sub(plane.position, inter.position));
	alpha = vec3_dot(t, dir);
	VEC3	npos = plane.position;
	while (alpha < 0)
	{
		npos = vec3_add(npos, vec3_scale(t, 10.f));
		d = vec3_distance(inter.position, npos);
		dir = vec3_normalize(vec3_sub(npos, inter.position));
		alpha = vec3_dot(t, dir);
	}
	while (vec3_dot(b, dir) < 0)
	{
		npos = vec3_add(npos, vec3_scale(b, 10.f));
		d = vec3_distance(inter.position, npos);
		dir = vec3_normalize(vec3_sub(npos, inter.position));
		alpha = vec3_dot(t, dir);
	}
	uv.x = cos(acosf(alpha)) * d / 5.f;
	uv.y = sin(acosf(alpha)) * d / 5.f;
	return (uv);
}
