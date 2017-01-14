/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/09 14:07:55 by gpinchon         ###   ########.fr       */
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
	fu = fabs(fu);
	fv = fabs(fv);
	int	u[4];
	int v[4];
	u[0] = u[2] = CLAMP((int)fu % img.size.x, 0, img.size.x);
	v[0] = v[1] = CLAMP((int)fv % img.size.y, 0, img.size.y);
	u[1] = u[3] = CLAMP((u[0] + 1) % img.size.x, 0, img.size.x);
	v[2] = v[3] = CLAMP((v[0] + 1) % img.size.y, 0, img.size.y);
	fu = fu - floorf(fu);
	fv = fv - floorf(fv);
	float weight[4];
	weight[0] = ((1 - fu) * (1 - fv));
	weight[1] = (fu * (1 - fv));
	weight[2] = ((1 - fu) * fv);
	weight[3] = (fu *  fv);
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

VEC2		sphere_uv(u_obj sphere, INTERSECT inter, TRANSFORM *t)
{
	float	phi;
	VEC2	uv;
	VEC3	vp;
	VEC3	vn;
	VEC3	ve;

	if (!t->rotation.x
	&& !t->rotation.y
	&& !t->rotation.z)
		vn = UPVEC;
	else
		vn = t->rotation;
	ve = vec3_cross(vn, (VEC3){0, 0, 1});
	vp = vec3_normalize(vec3_sub(inter.position, t->position));
	phi = acosf(-vec3_dot(vn, vp));
	uv.y = phi / M_PI + 1;
	uv.x = acosf(CLAMP(vec3_dot(vp, ve) / sin(phi), -1, 1)) / (2.f * M_PI) + 1;
	if (vec3_dot(vec3_cross(vn, ve), vp) <= 0)
		uv.x = 1 - uv.x + 1;
	return (uv);
	(void)sphere;
}

VEC2		cylinder_uv(u_obj o, INTERSECT inter, TRANSFORM *t)
{
	VEC2	uv;
	VEC3	vp;
	VEC3	vn;
	VEC3	ve;
	VEC3	cp;

	if (!t->rotation.x
	&& !t->rotation.y
	&& !t->rotation.z)
		vn = UPVEC;
	else
		vn = t->rotation;
	cp = vec3_sub(t->position, vec3_scale(t->rotation, o.cylinder.size ? o.cylinder.size : 10.f));
	ve = vec3_cross(vn, (VEC3){0, 0, 1});
	vp = vec3_normalize(vec3_sub(inter.position, cp));
	uv.x = acosf(CLAMP(vec3_dot(vp, ve) / sin(acosf(-vec3_dot(vn, vp))), -1, 1)) / (2.f * M_PI) + 1;
	if (vec3_dot(vec3_cross(vn, ve), vp) <= 0)
		uv.x = 1 - uv.x + 1;
	uv.y = sqrt(pow(vec3_distance(cp, inter.position), 2) - o.cylinder.radius2) / 10.f + 1;
	return (uv);
}

VEC2	plane_uv(u_obj plane, INTERSECT inter, TRANSFORM *tr)
{
	VEC2	uv;
	VEC3	t;
	VEC3	dir;
	float	alpha;
	float 	d;

	t = vec3_cross(vec3_negate(inter.normal), new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(inter.normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	VEC3	b = vec3_cross(t, inter.normal);
	d = vec3_distance(inter.position, tr->position);
	dir = vec3_normalize(vec3_sub(tr->position, inter.position));
	alpha = vec3_dot(t, dir);
	VEC3	npos = tr->position;
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
	uv.x = cos(acosf(alpha)) * d / 5.f + 1;
	uv.y = sin(acosf(alpha)) * d / 5.f + 1;
	return (uv);
	(void)plane;
}
