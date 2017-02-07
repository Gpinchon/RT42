/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 15:58:10 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/07 16:19:36 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline void	intersect_light_primitive(ENGINE *e, CAST_RETURN *ret,
	RTPRIMITIVE p)
{
	INTERSECT	in;
	TRANSFORM	t;

	t = p.transform ? p.transform->current :
		new_transform(new_vec3(0, 0, 0), UPVEC, new_vec3(1, 1, 1), UPVEC);
	if (e->inter_functions[p.prim.type]
	&& (in = e->inter_functions[p.prim.type](p.prim.data,
		ret->ray, &t)).intersects
	&& (ret->intersect.distance[0] == 0
		|| in.distance[0] < ret->intersect.distance[0]))
	{
		ret->intersect = in;
		if (p.material)
			ret->mtl = *p.material;
	}
}

CAST_RETURN			cast_light_ray(ENGINE *e, SCENE *s, RAY ray)
{
	UINT		i;
	RTPRIMITIVE	p;
	CAST_RETURN	ret;
	ARRAY		primitives;

	i = 0;
	ret.intersect.distance[0] = 0;
	ret.intersect.intersects = 0;
	ret.ray = ray;
	primitives = s->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		intersect_light_primitive(e, &ret, p);
		i++;
	}
	return (ret);
}
