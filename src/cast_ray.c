/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/04 22:39:21 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

BOOL	check_intersection(float intersection, float current)
{
	return (current == 0 || intersection < current);
}

VEC3	sample_normal_map(void *normal_map, VEC2 uv, MAT3 tbn)
{
	return (mat3_mult_vec3(tbn,
		vec3_normalize(vec3_sub(vec3_scale(sample_texture_filtered(normal_map, uv), 2), new_vec3(1, 1, 1)))));
}

MAT3		tbn_matrix(VEC3 normal)
{
	VEC3	t;

	t = vec3_cross(normal, new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize((vec3_cross(normal, t))), normal));
}

/*VEC2	sample_height_map(void	*height_map, VEC2 uv, CAST_RETURN *ret, RAY ray)
{
	VEC2	offset;
	float	depth;

	VEC3	V = mat3_mult_vec3(mat3_inverse(ret->tbn), ray.direction);
	depth = color_to_factor(sample_texture_filtered(height_map, uv));
	offset = vec2_scale(vec3_to_vec2(V), 0.05);
	offset = vec2_fdiv(offset, V.z * depth);
	return (vec2_sub(uv, offset));
}*/

VEC2	sample_height_map(void	*height_map, VEC2 uv, CAST_RETURN *ret, RAY ray)
{
	INTERSECT	inter = ret->intersect;
	VEC3	viewDir = mat3_mult_vec3(ret->tbn, ray.direction);
	const float numLayers = interp_linear(100, 50, fabs(vec3_dot(inter.normal, viewDir)));
	float layerDepth = 1.0 / numLayers;
	float currentLayerDepth = 0.0;
	VEC2 P = vec2_scale(vec3_to_vec2(viewDir), ret->mtl.parallax); 
	VEC2 deltaTexCoords = vec2_fdiv(P, numLayers);
	VEC2  currentTexCoords = uv;
	float currentDepthMapValue = 1 - sample_texture(height_map, currentTexCoords).x;
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords = vec2_sub(currentTexCoords, deltaTexCoords);
		currentDepthMapValue = 1 - sample_texture(height_map, currentTexCoords).x;
		currentLayerDepth += layerDepth;  
	}
	VEC2 prevTexCoords = vec2_add(currentTexCoords, deltaTexCoords);
	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = sample_texture(height_map, prevTexCoords).x - currentLayerDepth + layerDepth;
	float weight = afterDepth / (afterDepth - beforeDepth);
	VEC2 finalTexCoords = vec2_add(vec2_scale(prevTexCoords, weight), vec2_scale(currentTexCoords, (1.0 - weight)));
	float	finaldepth = sample_texture(height_map, finalTexCoords).x;
	ret->intersect.position = vec3_add(inter.position, vec3_scale(inter.normal, (1 - finaldepth) * ret->mtl.parallax));
	return (finalTexCoords); 	
}

void	get_ret_mtl(CAST_RETURN	*ret)
{
	MATERIAL	mtl;
	VEC2		uv;

	mtl = ret->mtl;
	uv = ret->uv;
	if (mtl.height_map)
		uv = ret->uv = sample_height_map(mtl.height_map, uv, ret, ret->ray);
	if (mtl.normal_map)
	{
		ret->intersect.normal = sample_normal_map(mtl.normal_map, uv, ret->tbn);
		//ret->tbn = tbn_matrix(ret->intersect.normal);
	}
	if (mtl.base_map)
		mtl.reflection_color = mtl.base_color = sample_texture_filtered(mtl.base_map, uv);
	if (mtl.rough_map)
		mtl.roughness = sample_texture_filtered(mtl.rough_map, uv).x;
	if (mtl.metal_map)
		mtl.metalness = sample_texture_filtered(mtl.metal_map, uv).x;
	if (mtl.ao_map)
		mtl.base_color = vec3_mult(mtl.base_color, sample_texture_filtered(mtl.ao_map, uv));
	ret->mtl = mtl;
}

CAST_RETURN	cast_ray(ENGINE *engine, SCENE *scene, RAY ray)
{
	UINT		i;
	INTERSECT	inter;
	RTPRIMITIVE	p;
	CAST_RETURN	ret;
	ARRAY		primitives;

	i = 0;
	ret.intersect.intersects = ret.intersect.distance[0] = 0;
	ret.ray = ray;
	primitives = scene->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		if (p.transform && !p.transformed)
		{
			update_transform(p.transform);
			p.prim.position = mat4_mult_vec3(p.transform->translate, p.transform->position);
			p.prim.direction = vec3_normalize(mat4_mult_vec3(p.transform->rotate, p.transform->rotation));
			p.transformed = true;
		}
		if (engine->inter_functions[p.prim.type]
		&& (inter = engine->inter_functions[p.prim.type](p.prim, ray)).intersects)
		{
			if (ret.intersect.distance[0] == 0 || inter.distance[0] < ret.intersect.distance[0])
			{
				ret.intersect = inter;
				ret.tbn = tbn_matrix(inter.normal);
				if (p.material)
					ret.mtl = *p.material;
				if (engine->uv_functions[p.prim.type])
					ret.uv = vec2_mult(engine->uv_functions[p.prim.type](p.prim, inter), ret.mtl.uv_scale);
			}
		}
		i++;
	}
	return (ret);
}

CAST_RETURN	cast_light_ray(ENGINE *engine, SCENE *scene, RAY ray)
{
	UINT		i;
	INTERSECT	inter;
	RTPRIMITIVE	p;
	CAST_RETURN	ret;
	ARRAY		primitives;

	i = 0;
	ret.intersect.intersects = ret.intersect.distance[0] = 0;
	ret.ray = ray;
	primitives = scene->primitives;
	while (i < primitives.length)
	{
		p = *((RTPRIMITIVE*)ezarray_get_index(primitives, i));
		if (p.transform && !p.transformed)
		{
			update_transform(p.transform);
			p.prim.position = mat4_mult_vec3(p.transform->translate, p.transform->position);
			p.prim.direction = vec3_normalize(mat4_mult_vec3(p.transform->rotate, p.transform->rotation));
			p.transformed = true;
		}
		if (engine->inter_functions[p.prim.type]
		&& (inter = engine->inter_functions[p.prim.type](p.prim, ray)).intersects
		&& (ret.intersect.distance[0] == 0 || inter.distance[0] < ret.intersect.distance[0]))
		{
			ret.intersect = inter;
			if (p.material)
				ret.mtl = *p.material;
		}
		i++;
	}
	return (ret);
}
