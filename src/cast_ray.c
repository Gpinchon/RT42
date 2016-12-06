/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/06 01:30:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

CAST_RETURN	cast_ray(ENGINE *engine, SCENE *scene, RAY ray)
{
	UINT		i;
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
		if (engine->inter_functions[prim->prim.type])
		{
			inter = engine->inter_functions[prim->prim.type](prim->prim, ray);
			if (inter.intersects && (inter.distance[0] < ret.intersect.distance[0] || ret.intersect.distance[0] == 0))
			{
				ret.intersect = inter;
				ret.rtprimitive = prim;
				if (ret.rtprimitive->material)
					ret.mtl = *ret.rtprimitive->material;
				if (ret.rtprimitive->prim.type == sphere)
					ret.uv = vec2_mult(sphere_uv(ret.rtprimitive->prim, ret.intersect), ret.mtl.uv_scale);
				else if (ret.rtprimitive->prim.type == cylinder)
					ret.uv = vec2_mult(cylinder_uv(ret.rtprimitive->prim, ret.intersect), ret.mtl.uv_scale);
				else if (ret.rtprimitive->prim.type == plane)
					ret.uv = vec2_mult(plane_uv(ret.rtprimitive->prim, ret.intersect), ret.mtl.uv_scale);
				if (ret.mtl.normal_map)
				{
					//ret.intersect.normal = vec3_mult(ret.intersect.normal, vec3_normalize(vec3_cross(ret.intersect.normal, get_texture_color(ret.mtl.normal_map, ret.uv))));
					//ret.intersect.normal = get_texture_color(ret.mtl.normal_map, ret.uv);
					//ret.intersect.normal = vec3_normalize(vec3_mult(ret.intersect.normal, get_texture_color(ret.mtl.normal_map, ret.uv)));
					//ret.intersect.normal = mat4_mult_vec3(mat4_inverse(prim->transform->matrix), get_texture_color(ret.mtl.normal_map, ret.uv));
					//printf("normal %f, %f, %f\n", ret.intersect.normal.x, ret.intersect.normal.y, ret.intersect.normal.z);
					VEC3 t = vec3_cross(ret.intersect.normal, (VEC3){0, 1, 0});
					//VEC3 v1 = vec3_cross(ret.intersect.normal, (VEC3){0, 0, 0});
					//VEC3 t;
					VEC3 b = vec3_cross(t, (VEC3){0, 1, 0});
					if (vec3_length(t) == 0)
					{
						t = vec3_cross(ret.intersect.normal, (VEC3){0, 0, 1});
						b = vec3_cross(t, (VEC3){0, 1, 0});
					}
					ret.intersect.normal = mat3_mult_vec3(new_mat3(t, b, ret.intersect.normal), get_texture_color(ret.mtl.normal_map, ret.uv));
					//printf("right %f, %f, %f\n", ret.intersect.normal.x, ret.intersect.normal.y, ret.intersect.normal.z);
				}
				if (ret.mtl.base_map)
					ret.mtl.reflection_color = ret.mtl.base_color = get_texture_color(ret.mtl.base_map, ret.uv);
				if (ret.mtl.rough_map)
					ret.mtl.roughness = color_to_factor(get_texture_color(ret.mtl.rough_map, ret.uv));
				if (ret.mtl.metal_map)
					ret.mtl.metalness = color_to_factor(get_texture_color(ret.mtl.metal_map, ret.uv));
			}
		}
		i++;
	}
	return (ret);
}