/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:52:19 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/14 23:23:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

BOOL	check_intersection(float intersection, float current)
{
	return (current == 0 || intersection < current);
}

VEC3	sample_normal_map(void *normal_map, VEC2 uv, MAT3 tbn)
{
	VEC3	tnorm = sample_texture_filtered(normal_map, uv);
	tnorm = vec3_sub(vec3_scale(tnorm, 2), new_vec3(1, 1, 1));
	tnorm.x *= -1;
	tnorm.y *= -1;
	return (vec3_normalize(mat3_mult_vec3(tbn,
			vec3_normalize(tnorm))));
}

float	fract(float f)
{
	return (f - (int)f);
}

VEC3 vec3_orthogonal(VEC3 v)
{
	float k = fract(fabs(v.x) + 0.5);
	return new_vec3(-v.y, v.x - k * v.z, k * v.y);
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

	//t = vec3_orthogonal(vec3_negate(normal));
	//t = vec3_cross(normal, vec3_orthogonal(normal));
	t = vec3_cross(normal, new_vec3(0.0, 1.0, 0.0));
	if (!vec3_length(t))
		t = vec3_cross(normal, new_vec3(0.0, 0.0, 1.0));
	t = vec3_normalize(t);
	return (new_mat3(t, vec3_normalize(vec3_cross(vec3_negate(normal), t)), normal));
}

VEC2	sample_height_map(void	*height_map, VEC2 uv, CAST_RETURN *ret, RAY ray)
{
	VEC3	viewDir = mat3_mult_vec3(mat3_inverse(ret->tbn), ray.direction);
	const float numLayers = interp_linear(50, 100, fabs(viewDir.z));
	float layerDepth = 1.0 / numLayers;
	float currentLayerDepth = 0.0;
	VEC2 deltaTexCoords = vec2_fdiv(vec2_scale(vec3_to_vec2(viewDir), ret->mtl.parallax), numLayers);
	VEC2  currentTexCoords = uv;
	float currentDepthMapValue = 1 - sample_texture_filtered(height_map, currentTexCoords).x;
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords = vec2_sub(currentTexCoords, deltaTexCoords);
		currentDepthMapValue = 1 - sample_texture_filtered(height_map, currentTexCoords).x;
		currentLayerDepth += layerDepth;  
	}
	VEC2 prevTexCoords = vec2_add(currentTexCoords, deltaTexCoords);
	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float weight = afterDepth / (afterDepth - 1 - sample_texture_filtered(height_map, prevTexCoords).x - currentLayerDepth + layerDepth);
	return (vec2_add(vec2_scale(prevTexCoords, weight), vec2_scale(currentTexCoords, (1.0 - weight)))); 	
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
		ret->intersect.normal = sample_normal_map(mtl.normal_map, uv, ret->tbn);
	if (mtl.base_map)
		mtl.reflection_color = mtl.base_color = sample_texture_filtered(mtl.base_map, uv);
	if (mtl.rough_map)
		mtl.roughness = sample_texture_filtered(mtl.rough_map, uv).x;
	if (mtl.metal_map)
		mtl.metalness = sample_texture_filtered(mtl.metal_map, uv).x;
	if (mtl.alpha_map)
		mtl.alpha = sample_texture_filtered(mtl.alpha_map, uv).x;
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
	TRANSFORM	t;

	i = 0;
	vml_memset(&ret, 0, sizeof(CAST_RETURN));
	ret.ray = ray;
	primitives = scene->primitives;
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
		if (engine->inter_functions[p.prim.type]
		&& (inter = engine->inter_functions[p.prim.type](p.prim.data, ray, &t)).intersects)
		{
			if (ret.intersect.distance[0] == 0 || inter.distance[0] < ret.intersect.distance[0])
			{
				ret.intersect = inter;
				if (p.prim.type == plane)
					ret.tbn = plane_tbn_matrix(inter.normal);
				else
					ret.tbn = tbn_matrix(inter.normal, t.rotation);
				if (p.material)
					ret.mtl = *p.material;
				if (engine->uv_functions[p.prim.type])
					ret.uv = vec2_mult(engine->uv_functions[p.prim.type](p.prim.data, inter, &t), ret.mtl.uv_scale);
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
	TRANSFORM	t;

	i = 0;
	ret.intersect.intersects = ret.intersect.distance[0] = 0;
	ret.ray = ray;
	primitives = scene->primitives;
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
		if (engine->inter_functions[p.prim.type]
		&& (inter = engine->inter_functions[p.prim.type](p.prim.data, ray, &t)).intersects
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
