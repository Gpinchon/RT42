/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/07 23:32:45 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

VEC3 mat3_mult_vec32(MAT3 m, VEC3 v)
{
	VEC3	out;

	out.x = v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6];
    out.y = v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7];
    out.z = v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8];
    return (out);
}

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
					VEC3	t = vec3_cross(ret.intersect.normal, new_vec3(0.0, 1.0, 0.0)); 
					VEC3	b;
					VEC3	n = ret.intersect.normal;
					if (!vec3_length(t))
						t = vec3_cross(ret.intersect.normal, new_vec3(0.0, 0.0, 1.0));
					t = vec3_normalize(t);
					b = vec3_normalize((vec3_cross(n, t)));
					VEC3	map_n = get_texture_color(ret.mtl.normal_map, ret.uv);
					map_n = vec3_normalize(vec3_sub(vec3_scale(map_n, 2), new_vec3(1, 1, 1)));
					MAT3	tbn = new_mat3(t, b, n);
					ret.intersect.normal = vec3_normalize(mat3_mult_vec3(tbn, map_n));
				}
				if (ret.mtl.base_map)
					ret.mtl.reflection_color = ret.mtl.base_color = get_texture_color(ret.mtl.base_map, ret.uv);
				if (ret.mtl.rough_map)
					ret.mtl.roughness = color_to_factor(get_texture_color(ret.mtl.rough_map, ret.uv));
				if (ret.mtl.metal_map)
					ret.mtl.metalness = color_to_factor(get_texture_color(ret.mtl.metal_map, ret.uv));
				if (ret.mtl.ao_map)
					ret.mtl.base_color = vec3_mult(ret.mtl.base_color, get_texture_color(ret.mtl.ao_map, ret.uv));
				if (ret.mtl.height_map)
					ret.intersect.position = vec3_add(ret.intersect.position, vec3_scale(ret.intersect.normal, 1 - color_to_factor(get_texture_color(ret.mtl.height_map, ret.uv))));
			}
		}
		i++;
	}
	return (ret);
}