/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 19:47:34 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

BOOL	check_intersection(float intersection, float current)
{
	return (current == 0 || intersection < current);
}

void	sample_normal(void *normal_map, VEC2 uv, INTERSECT *inter)
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
			get_texture_color(normal_map, uv), 2),new_vec3(1, 1, 1)))));
}

CAST_RETURN	cast_ray(ENGINE *engine, SCENE *scene, RAY ray)
{
	UINT		i;
	VEC2		uv;
	MATERIAL	mtl;
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
			if (prim->material)
				mtl = *prim->material;
			if (prim->prim.type == sphere)
				uv = vec2_mult(sphere_uv(prim->prim, inter), mtl.uv_scale);
			else if (prim->prim.type == cylinder
			|| prim->prim.type == cone)
				uv = vec2_mult(cylinder_uv(prim->prim, inter), mtl.uv_scale);
			else if (prim->prim.type == plane)
				uv = vec2_mult(plane_uv(prim->prim, inter), mtl.uv_scale);
			sample_normal(mtl.normal_map, uv, &inter);
			if (mtl.height_map)
			{
				inter.position = vec3_add(inter.position, vec3_scale(inter.normal, color_to_factor(get_texture_color(mtl.height_map, uv))));
				inter.distance[0] = vec3_distance(inter.position, ray.origin);
			}
			if (check_intersection(inter.distance[0], ret.intersect.distance[0]))
			{
				if (mtl.base_map)
					mtl.reflection_color = mtl.base_color = get_texture_color(mtl.base_map, uv);
				if (mtl.rough_map)
					mtl.roughness = color_to_factor(get_texture_color(mtl.rough_map, uv));
				if (mtl.metal_map)
					mtl.metalness = color_to_factor(get_texture_color(mtl.metal_map, uv));
				if (mtl.ao_map)
					mtl.base_color = vec3_mult(mtl.base_color, get_texture_color(mtl.ao_map, uv));
				ret.intersect = inter;
				ret.rtprimitive = prim;
				ret.mtl = mtl;
				ret.uv = uv;
			}
		}
		i++;
	}
	return (ret);
}