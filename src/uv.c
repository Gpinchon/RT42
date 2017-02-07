/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:46:46 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/07 22:43:57 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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

VEC2	plane_uv(u_obj plane, INTERSECT i, TRANSFORM *tr)
{
	VEC2	uv;
	VEC3	t;
	VEC3	dir;
	VEC3	b;
	VEC3	npos;
	float	alpha;
	float 	d;

	uv = new_vec2(0, 0);
	t = vec3_normalize(vec3_cross(i.normal, vec3_orthogonal(tr->rotation)));
	b = vec3_normalize(vec3_negate(vec3_cross(t, i.normal)));
	d = vec3_distance(i.position, tr->position);
	dir = vec3_normalize(vec3_sub(tr->position, i.position));
	alpha = vec3_dot(t, dir);
	npos = tr->position;
	while ((alpha = vec3_dot(t, dir)) < 0)
	{
		npos = vec3_add(npos, vec3_scale(t, 10.f));
		d = vec3_distance(i.position, npos);
		dir = vec3_normalize(vec3_sub(npos, i.position));
	}
	while (vec3_dot(b, dir) < 0)
	{
		npos = vec3_add(npos, vec3_scale(b, 10.f));
		d = vec3_distance(i.position, npos);
		dir = vec3_normalize(vec3_sub(npos, i.position));
		alpha = vec3_dot(t, dir);
	}
	if (alpha < 1)
		uv = new_vec2(fract(cos(acosf(alpha)) * d / 5.f + 1),
		fract(sin(acosf(alpha)) * d / 5.f + 1));
	return (uv);
	(void)plane;
}
