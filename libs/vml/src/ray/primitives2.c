/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:44:28 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/11 15:59:19 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vml.h>

static inline INTERSECT	inter_con(OBJ cp, TRANSFORM t,
	INTERSECT i, VEC3 f)
{
	VEC3	v;

	v = vec3_sub(i.position, t.position);
	if (vec3_dot(t.rotation, vec3_normalize(v)) < 0)
		i.intersects = 0;
	else if (cp.cone.size > 0)
		i.intersects = (vec3_distance(t.position,
			vec3_add(t.position, vec3_scale(t.rotation,
			f.x))) <= cp.cone.size);
	if (i.intersects)
		i.normal = vec3_normalize(vec3_sub(v,
			vec3_scale(t.rotation, f.z * f.x)));
	return (i);
}

INTERSECT				intersect_cone(OBJ cp, RAY r, TRANSFORM *transform)
{
	INTERSECT	i;
	VEC3		v;
	VEC3		f;
	TRANSFORM	t;

	t = *transform;
	v = vec3_sub(r.origin, t.position);
	f = (VEC3){vec3_dot(r.direction, t.rotation), vec3_dot(v, t.rotation),
	1 + cp.cone.radius2};
	i.intersects = (solve_quadratic(vec3_dot(r.direction, r.direction) -
	f.z * pow(f.x, 2), 2 * (vec3_dot(r.direction, v) - f.z * f.x * f.y),
	vec3_dot(v, v) - f.z * pow(f.y, 2), i.distance)
	&& intersect_test(i.distance));
	if (i.intersects)
	{
		i.distance[0] = i.distance[0] <= 0 ? i.distance[1] : i.distance[0];
		i.position = intersect_compute_position(r, i.distance[0]);
		f.x = f.x * i.distance[0] + f.y;
		i = inter_con(cp, t, i, f);
	}
	return (i);
}

static inline INTERSECT	inter_cyl(OBJ p, t_ray r, TRANSFORM *t, INTERSECT i)
{
	if (!(i.intersects = intersect_test(i.distance)))
		return (i);
	if (i.distance[0] <= 0)
	{
		i.distance[0] = i.distance[1];
		i.position = intersect_compute_position(r, i.distance[0]);
		i.normal = vec3_negate(cylinder_normal(i.position, p, t));
	}
	else
	{
		i.position = intersect_compute_position(r, i.distance[0]);
		i.normal = cylinder_normal(i.position, p, t);
	}
	return (i);
}

INTERSECT				intersect_cylinder(OBJ p, t_ray r, TRANSFORM *t)
{
	t_vec3		v[5];
	INTERSECT	i;

	i = new_intersect();
	v[0] = vec3_proj(t->position, t->rotation);
	v[1] = vec3_proj(r.origin, t->rotation);
	v[2] = vec3_proj(r.direction, t->rotation);
	v[3] = vec3_sub(r.direction, v[2]);
	v[4] = vec3_sub(vec3_sub(r.origin, v[1]), vec3_sub(t->position, v[0]));
	if (!(i.intersects = solve_quadratic(vec3_dot(v[3], v[3]),
		vec3_dot(v[4], v[3]) * 2.0,
		vec3_dot(v[4], v[4]) - (p.cylinder.radius2), i.distance)))
		return (i);
	if (p.cylinder.size > 0)
	{
		i.distance[0] *= (vec3_length(vec3_sub(vec3_add(v[1], vec3_scale(v[2],
			i.distance[0])), v[0])) <= p.cylinder.size / 2.f);
		i.distance[1] *= (vec3_length(vec3_sub(vec3_add(v[1], vec3_scale(v[2],
			i.distance[1])), v[0])) <= p.cylinder.size / 2.f);
	}
	return (inter_cyl(p, r, t, i));
}
