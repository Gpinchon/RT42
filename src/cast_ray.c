/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/23 17:36:33 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline BOOL	check_intersection(float current, float intersection)
{
	return (current == 0 || intersection < current);
}

MAT3		tbn_matrix(VEC3 n, VEC3 pdir)
{
	VEC3	t;

	t = vec3_cross(n, pdir);
	if (!vec3_length(t))
		t = vec3_cross(n, vec3_orthogonal(n));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize(vec3_cross(n, t)), n));
}

MAT3		plane_tbn_matrix(VEC3 n)
{
	VEC3	t;

	t = vec3_cross(vec3_negate(n), new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(n, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize(vec3_cross(vec3_negate(n), t)), n));
}

static inline void	intersect_primitive(ENGINE *e, RTPRIMITIVE *p, CAST_RETURN *ret)
{
	INTERSECT	in;
	TRANSFORM	t;

	t = p->transform ?
	new_transform(p->transform->current.position, p->transform->current.rotation,
	p->transform->current.scaling, p->transform->current.up) :
	new_transform(new_vec3(0, 0, 0), UPVEC, new_vec3(1, 1, 1), UPVEC);
	if (e->inter_functions[p->prim.type]
	&& (in = e->inter_functions[p->prim.type](p->prim.data, ret->ray, &t)).intersects
	&& check_intersection(ret->intersect.distance[0], in.distance[0]))
	{
		ret->intersect = in;
		ret->tbn = p->prim.type == plane ? plane_tbn_matrix(in.normal) :
			tbn_matrix(in.normal, t.rotation);
		if (p->material)
			ret->mtl = *p->material;
		if (e->uv_functions[p->prim.type])
			ret->uv = vec2_mult(e->uv_functions[p->prim.type](p->prim.data, in, &t), ret->mtl.uv_scale);
	}
}

CAST_RETURN	cast_ray(ENGINE *e, SCENE *s, RAY ray)
{
	UINT		i;
	CAST_RETURN	ret;
	ARRAY		primitives;

	i = 0;
	vml_memset(&ret, 0, sizeof(CAST_RETURN));
	ret.ray = ray;
	primitives = s->primitives;
	while (i < primitives.length)
	{
		intersect_primitive(e, ezarray_get_index(primitives, i), &ret);
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
