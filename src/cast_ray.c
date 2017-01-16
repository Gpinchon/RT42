/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/16 14:52:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

BOOL	check_intersection(float intersection, float current)
{
	return (current == 0 || intersection < current);
}

MAT3		tbn_matrix(VEC3 normal, VEC3 pdir)
{
	VEC3	t;

	t = vec3_cross(normal, pdir);
	if (!vec3_length(t))
		t = vec3_cross(normal, vec3_orthogonal(normal));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize(vec3_cross(normal, t)), normal));
}

MAT3		plane_tbn_matrix(VEC3 normal)
{
	VEC3	t;

	t = vec3_cross(normal, new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize(vec3_cross(vec3_negate(normal), t)), normal));
}



CAST_RETURN	cast_ray(ENGINE *e, SCENE *s, RAY ray)
{
	UINT		i;
	INTERSECT	in;
	RTPRIMITIVE	p;
	CAST_RETURN	ret;
	ARRAY		primitives;
	TRANSFORM	t;

	i = 0;
	vml_memset(&ret, 0, sizeof(CAST_RETURN));
	ret.ray = ray;
	primitives = s->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		t.rotation = UPVEC;
		t.position = new_vec3(0, 0, 0);
		if (p.transform)
		{
			t.position = p.transform->current.position;
			t.rotation = p.transform->current.rotation;
		}
		if (e->inter_functions[p.prim.type]
		&& (in = e->inter_functions[p.prim.type](p.prim.data, ray, &t)).intersects)
		{
			if (ret.intersect.distance[0] == 0 || in.distance[0] < ret.intersect.distance[0])
			{
				ret.intersect = in;
				if (p.prim.type == plane)
					ret.tbn = plane_tbn_matrix(in.normal);
				else
					ret.tbn = tbn_matrix(in.normal, t.rotation);
				if (p.material)
					ret.mtl = *p.material;
				if (e->uv_functions[p.prim.type])
					ret.uv = vec2_mult(e->uv_functions[p.prim.type](p.prim.data, in, &t), ret.mtl.uv_scale);
			}
		}
		i++;
	}
	return (ret);
}

CAST_RETURN	cast_light_ray(ENGINE *e, SCENE *s, RAY ray)
{
	UINT		i;
	INTERSECT	in;
	RTPRIMITIVE	p;
	CAST_RETURN	ret;
	ARRAY		primitives;
	TRANSFORM	t;

	i = 0;
	ret.intersect.intersects = ret.intersect.distance[0] = 0;
	ret.ray = ray;
	primitives = s->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		t.rotation = UPVEC;
		t.position = new_vec3(0, 0, 0);
		if (p.transform)
		{
			t.position = p.transform->current.position;
			t.rotation = p.transform->current.rotation;
		}
		if (e->inter_functions[p.prim.type]
		&& (in = e->inter_functions[p.prim.type](p.prim.data, ray, &t)).intersects
		&& (ret.intersect.distance[0] == 0 || in.distance[0] < ret.intersect.distance[0]))
		{
			ret.intersect = in;
			if (p.material)
				ret.mtl = *p.material;
		}
		i++;
	}
	return (ret);
}
