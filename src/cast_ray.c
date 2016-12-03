/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/03 00:09:45 by gpinchon         ###   ########.fr       */
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
			/*if (prim->prim.type == plane)
				prim->prim.direction = prim->transform->rotation;*/
			prim->transformed = true;
		}
		if (engine->inter_functions[prim->prim.type])
		{
			inter = engine->inter_functions[prim->prim.type](prim->prim, ray);
			if (inter.intersects && (inter.distance[0] < ret.intersect.distance[0] || ret.intersect.distance[0] == 0))
			{
				ret.intersect = inter;
				ret.rtprimitive = prim;
				if (ret.rtprimitive->prim.type == sphere)
				{
					ret.uv = sphere_uv(ret.rtprimitive->prim, ret.intersect);
					if (ret.rtprimitive->material->normal_map)
					{
						ret.intersect.normal = vec3_normalize(vec3_mult(ret.intersect.normal, vec3_normalize(get_texture_color(ret.rtprimitive->material->normal_map, ret.uv))));
						printf("%f, %f, %f\n",
							get_texture_color(ret.rtprimitive->material->normal_map, ret.uv).x,
							get_texture_color(ret.rtprimitive->material->normal_map, ret.uv).y,
							get_texture_color(ret.rtprimitive->material->normal_map, ret.uv).z);
					}
				}
			}
		}
		i++;
	}
	return (ret);
}