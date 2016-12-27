/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/27 16:04:07 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

BOOL	check_intersection(float intersection, float current)
{
	return (current == 0 || intersection < current);
}

void	sample_normal_map(void *normal_map, VEC2 uv, INTERSECT *inter)
{
	VEC3	t;

	if (!normal_map)
		return ;
	t = vec3_cross(inter->normal, new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(inter->normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	inter->normal = vec3_normalize(mat3_mult_vec3(new_mat3(t,
		vec3_normalize((vec3_cross(inter->normal, t))), inter->normal),
		vec3_normalize(vec3_sub(vec3_scale(
			sample_texture_filtered(normal_map, uv), 2),new_vec3(1, 1, 1)))));
}

CAST_RETURN	cast_ray(ENGINE *engine, SCENE *scene, RAY ray)
{
	UINT		i;
	VEC2		uv;
	INTERSECT	inter;
	RTPRIMITIVE	*prim;
	CAST_RETURN	ret;

	i = 0;
	vml_memset(&ret, 0, sizeof(CAST_RETURN));
	while (i < scene->primitives.length)
	{
		prim = ezarray_get_index(scene->primitives, i);
		if (prim->transform && !prim->transformed)
		{
			update_transform(prim->transform);
			prim->prim.position = mat4_mult_vec3(prim->transform->translate, prim->transform->position);
			prim->prim.direction = vec3_normalize(mat4_mult_vec3(prim->transform->rotate, prim->transform->rotation));
			prim->transformed = true;
		}
		if (engine->inter_functions[prim->prim.type]
		&& (inter = engine->inter_functions[prim->prim.type](prim->prim, ray)).intersects)
		{
			if (ret.intersect.distance[0] == 0 || inter.distance[0] < ret.intersect.distance[0])
			{
				if (prim->material)
					ret.mtl = *prim->material;
				if (engine->uv_functions[prim->prim.type])
					uv = vec2_mult(engine->uv_functions[prim->prim.type](prim->prim, inter), ret.mtl.uv_scale);
				sample_normal_map(ret.mtl.normal_map, uv, &inter);
				if (ret.mtl.height_map)
					inter.position = vec3_add(inter.position, vec3_scale(inter.normal, 10 * color_to_factor(sample_texture_filtered(ret.mtl.height_map, uv))));
				if (ret.mtl.base_map)
					ret.mtl.reflection_color = ret.mtl.base_color = sample_texture_filtered(ret.mtl.base_map, uv);
				if (ret.mtl.rough_map)
					ret.mtl.roughness = color_to_factor(sample_texture_filtered(ret.mtl.rough_map, uv));
				if (ret.mtl.metal_map)
					ret.mtl.metalness = color_to_factor(sample_texture_filtered(ret.mtl.metal_map, uv));
				if (ret.mtl.ao_map)
					ret.mtl.base_color = vec3_mult(ret.mtl.base_color, sample_texture_filtered(ret.mtl.ao_map, uv));
				ret.intersect = inter;
				ret.rtprimitive = prim;
				ret.uv = uv;
			}
		}
		i++;
	}
	return (ret);
}