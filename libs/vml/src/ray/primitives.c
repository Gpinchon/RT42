/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 19:25:25 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/13 18:49:21 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

static inline VEC3	compute_tp(OBJ p, t_ray r, TRANSFORM *tr, VEC3 *tp)
{
	tp[0] = mat4_mult_vec3(tr->transform, p.triangle.point[0]);
	tp[1] = mat4_mult_vec3(tr->transform, p.triangle.point[1]);
	tp[2] = mat4_mult_vec3(tr->transform, p.triangle.point[2]);
	tp[1] = vec3_sub(tp[1], tp[0]);
	tp[2] = vec3_sub(tp[2], tp[0]);
	tp[0] = vec3_sub(r.origin, tp[0]);
	return (vec3_cross(r.direction, tp[2]));
}

INTERSECT			intersect_triangle(OBJ p, t_ray r, TRANSFORM *tr)
{
	VEC3		tp[3];
	VEC3		qvec;
	VEC3		pvec;
	VEC3		fact;
	INTERSECT	i;

	i = new_intersect();
	pvec = compute_tp(p, r, tr, tp);
	fact.z = 1 / vec3_dot(tp[1], pvec);
	fact.x = vec3_dot(tp[0], pvec) * fact.z;
	if (fact.x < 0 || fact.x > 1)
		return (i);
	qvec = vec3_cross(tp[0], tp[1]);
	fact.y = vec3_dot(r.direction, qvec) * fact.z;
	if (fact.y < 0 || fact.x + fact.y > 1)
		return (i);
	i.distance[0] = vec3_dot(tp[2], qvec) * fact.z;
	if (i.distance[0] <= 0)
		return (i);
	i.position = intersect_compute_position(r, i.distance[0]);
	i.normal = (VEC3){tp[1].y * tp[2].z - tp[1].z * tp[2].y,
						tp[1].z * tp[2].x - tp[1].x * tp[2].z,
						tp[1].x * tp[2].y - tp[1].y * tp[2].x};
	i.intersects = 1;
	return (i);
}

INTERSECT			intersect_sphere(OBJ p, t_ray r, TRANSFORM *t)
{
	t_vec3		eye;
	INTERSECT	inter;

	inter = new_intersect();
	eye = vec3_sub(r.origin, t->position);
	if (!(inter.intersects = solve_quadratic(
				vec3_dot(r.direction, r.direction),
				vec3_dot(eye, r.direction) * 2.0,
				vec3_dot(eye, eye) - (p.sphere.radius2),
				inter.distance) && intersect_test(inter.distance)))
		return (inter);
	if (inter.distance[0] <= 0)
	{
		inter.distance[0] = inter.distance[1];
		inter.position = intersect_compute_position(r, inter.distance[0]);
		inter.normal = vec3_negate(sphere_normal(inter.position, p, t));
	}
	else
	{
		inter.position = intersect_compute_position(r, inter.distance[0]);
		inter.normal = sphere_normal(inter.position, p, t);
	}
	return (inter);
}

inline INTERSECT	intersect_plane(OBJ p, t_ray r, TRANSFORM *tr)
{
	INTERSECT	inter;
	t_vec3		normal;
	float		denom;
	float		t;

	inter = new_intersect();
	normal = vec3_negate(tr->rotation);
	denom = vec3_dot(normal, r.direction);
	if (!float_equal(denom, 0.f))
	{
		if ((t = vec3_dot(vec3_sub(tr->position, r.origin), normal) / denom)
			>= FLOAT_ZERO)
		{
			inter.intersects = 1;
			inter.distance[0] = t;
			inter.distance[1] = inter.distance[0];
			inter.position = intersect_compute_position(r, inter.distance[0]);
			inter.normal = plane_normal(inter.position, p, tr);
			if (denom < 0)
				inter.normal = vec3_negate(inter.normal);
		}
	}
	return (inter);
}

INTERSECT			intersect_disc(OBJ d, t_ray r, TRANSFORM *transform)
{
	INTERSECT	inter;

	inter = intersect_plane(d, r, transform);
	inter.intersects = inter.intersects
	&& vec3_distance(inter.position, transform->position) <= d.disc.radius;
	return (inter);
}
