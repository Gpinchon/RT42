/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:46:46 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/15 15:31:01 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/*
** Cramer rules ! (boys, they wanna have pun)
*/

VEC2	triangle_uv(t_obj o, INTERSECT i, TRANSFORM *tr)
{
	VEC3		tp[3];
	VEC2		uv;
	VEC3		v[3];
	float		d[5];
	float		invd;

	tp[0] = mat4_mult_vec3(tr->transform, o.triangle.point[0]);
	tp[1] = mat4_mult_vec3(tr->transform, o.triangle.point[1]);
	tp[2] = mat4_mult_vec3(tr->transform, o.triangle.point[2]);
	v[0] = vec3_sub(tp[2], tp[0]);
	v[1] = vec3_sub(tp[1], tp[0]);
	v[2] = vec3_sub(i.position, tp[0]);
	d[0] = vec3_dot(v[0], v[0]);
	d[1] = vec3_dot(v[0], v[1]);
	d[2] = vec3_dot(v[0], v[2]);
	d[3] = vec3_dot(v[1], v[1]);
	d[4] = vec3_dot(v[1], v[2]);
	invd = 1 / (d[0] * d[3] - d[1] * d[1]);
	uv.x = ((d[3] * d[2] - d[1] * d[4]) * invd);
	uv.y = ((d[0] * d[4] - d[1] * d[2]) * invd);
	uv.x = 1.f - uv.y - uv.x;
	return (uv);
}

VEC2	sphere_uv(t_obj sphere, INTERSECT inter, TRANSFORM *t)
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

VEC2	cylinder_uv(t_obj o, INTERSECT inter, TRANSFORM *t)
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
	cp = vec3_sub(t->position, vec3_scale(t->rotation, o.cylinder.size ?
		o.cylinder.size : 10.f));
	if (!vec3_length(ve = vec3_cross(vn, (VEC3){0, 0, 1})))
		ve = vec3_cross(vn, (VEC3){0, 1, 0});
	vp = vec3_normalize(vec3_sub(inter.position, cp));
	uv.x = acosf(CLAMP(vec3_dot(vp, ve) /
		sin(acosf(-vec3_dot(vn, vp))), -1, 1)) / (2.f * M_PI) + 1;
	if (vec3_dot(vec3_cross(vn, ve), vp) <= 0)
		uv.x = 1 - uv.x + 1;
	uv.y = sqrt(fabs(pow(vec3_distance(cp, inter.position), 2) -
			o.cylinder.radius2)) / (10 * o.cylinder.radius) + 1;
	uv = new_vec2(fract(uv.x), fract(uv.y));
	return (uv);
}

VEC2	plane_uv(t_obj plane, INTERSECT i, TRANSFORM *t)
{
	VEC3	tb[2];
	VEC3	d;
	VEC3	p;
	float	alpha;
	float	l;

	tb[0] = vec3_normalize(vec3_cross(i.normal, vec3_orthogonal(t->rotation)));
	tb[1] = vec3_normalize(vec3_negate(vec3_cross(tb[0], i.normal)));
	d = vec3_normalize(vec3_sub(t->position, i.position));
	p = t->position;
	while ((alpha = vec3_dot(tb[0], d)) < 0)
	{
		p = vec3_add(p, vec3_scale(tb[0], 10.f));
		d = vec3_normalize(vec3_sub(p, i.position));
	}
	while (vec3_dot(tb[1], (d = vec3_normalize(vec3_sub(p, i.position)))) < 0)
		p = vec3_add(p, vec3_scale(tb[1], 10.f));
	l = vec3_distance(i.position, p);
	if ((alpha = vec3_dot(tb[0], d)) < 1)
	{
		return (new_vec2(fract(cos(acosf(alpha)) * l / 5.f + 1),
				fract(sin(acosf(alpha)) * l / 5.f + 1)));
	}
	return (new_vec2(0, 0));
	(void)plane;
}
