/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/02 16:18:06 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

BOOL	check_intersection(float intersection, float current)
{
	return (current == 0 || intersection < current);
}

void	sample_normal_map(void *normal_map, VEC2 uv, CAST_RETURN *ret)
{
	if (!normal_map)
		return ;
	ret->intersect.normal = vec3_normalize(mat3_mult_vec3(ret->tbn,
		vec3_normalize(vec3_sub(vec3_scale(sample_texture_filtered(normal_map, uv), 2), new_vec3(1, 1, 1)))));
}

MAT3		tbn_matrix(INTERSECT *inter)
{
	VEC3	t;

	t = vec3_cross(inter->normal, new_vec3(0.0, -1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(inter->normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize((vec3_cross(inter->normal, t))), inter->normal));
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
	/*VEC3	tvpos = mat3_mult_vec3(ret->tbn, ray.origin);
	VEC3	tpos = mat3_mult_vec3(ret->tbn, ret->intersect.position);
	VEC3	viewDir = vec3_normalize(vec3_sub(tvpos, tpos));
	float height =  1 - sample_texture(height_map, uv).x;    
    VEC2	p = vec2_scale(vec2_fdiv(vec3_to_vec2(viewDir), viewDir.z), (height * 0.05));
    return vec2_sub(uv, p);*/
    /*VEC3	tvpos = mat3_mult_vec3(ret->tbn, ray.origin);
	VEC3	tpos = mat3_mult_vec3(ret->tbn, ret->intersect.position);*/
	//VEC3	viewDir = vec3_normalize(vec3_sub(tvpos, tpos));
	//VEC3	V = mat3_mult_vec3(ret->tbn, e);
	 // number of depth layers
	VEC3	viewDir = mat3_mult_vec3(ret->tbn, ray.direction);
    const float numLayers = interp_linear(100, 50, abs(vec3_dot(ret->intersect.normal, viewDir)));
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

	// get depth after and before collision for linear interpolation
	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = sample_texture(height_map, prevTexCoords).x - currentLayerDepth + layerDepth;
	 
	// interpolation of texture coordinates
	float weight = afterDepth / (afterDepth - beforeDepth);
	VEC2 finalTexCoords = vec2_add(vec2_scale(prevTexCoords, weight), vec2_scale(currentTexCoords, (1.0 - weight)));
	float	finaldepth = sample_texture(height_map, finalTexCoords).x;
	ret->intersect.position = vec3_add(ret->intersect.position, vec3_scale(ret->intersect.normal, (1 - finaldepth) * ret->mtl.parallax));
	return (finalTexCoords); 	
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
				ret.intersect = inter;
				ret.tbn = tbn_matrix(&inter);
				if (prim->material)
					ret.mtl = *prim->material;
				if (engine->uv_functions[prim->prim.type])
					uv = vec2_mult(engine->uv_functions[prim->prim.type](prim->prim, inter), ret.mtl.uv_scale);
				if (ret.mtl.height_map)
					uv = sample_height_map(ret.mtl.height_map, uv, &ret, ray);
				sample_normal_map(ret.mtl.normal_map, uv, &ret);
					//inter.position = vec3_add(inter.position, vec3_scale(inter.normal, color_to_factor(sample_texture_filtered(ret.mtl.height_map, uv))));
				if (ret.mtl.base_map)
					ret.mtl.reflection_color = ret.mtl.base_color = sample_texture_filtered(ret.mtl.base_map, uv);
				if (ret.mtl.rough_map)
					ret.mtl.roughness = color_to_factor(sample_texture_filtered(ret.mtl.rough_map, uv));
				if (ret.mtl.metal_map)
					ret.mtl.metalness = color_to_factor(sample_texture_filtered(ret.mtl.metal_map, uv));
				if (ret.mtl.ao_map)
					ret.mtl.base_color = vec3_mult(ret.mtl.base_color, sample_texture_filtered(ret.mtl.ao_map, uv));
			}
		}
		i++;
	}
	return (ret);
}