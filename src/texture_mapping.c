/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:57:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/16 14:52:24 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_point2	map_uv(void *image, VEC2 uv)
{
	IMGDATA		img;

	img = get_image_data(image);
	return ((t_point2){
		CLAMP((int)(img.size.x * uv.x) % img.size.x, 0, img.size.x - 1),
		CLAMP((int)(img.size.y * uv.y) % img.size.y, 0, img.size.y - 1)
	});
}

VEC3		sample_texture(void *image, VEC2 uv)
{
	t_point2	tex;
	IMGDATA		img;
	UCHAR		*pixel;
	VEC3		color;

	if (!image)
		return ((VEC3){0, 0, 0});
	color = (VEC3){0, 0, 0};
	tex = map_uv(image, uv);
	img = get_image_data(image);
	pixel = img.pixels + (tex.y * img.sizeline + tex.x * img.opp);
	if (img.opp > 2)
	{
		color.x = pixel[2] / 255.f;
		color.y = pixel[1] / 255.f;
		color.z = pixel[0] / 255.f;
	}
	else if (img.opp == 1)
	{
		color.x = color.y = color.z = pixel[0] / 255.f;
	}
	return (color);
}

VEC3		sample_texture_filtered(void *image, VEC2 uv)
{
	IMGDATA		img;
	UCHAR		*pixel;
	VEC3		color;

	if (!image)
		return ((VEC3){0, 0, 0});
	color = (VEC3){0, 0, 0};
	img = get_image_data(image);
	float fu = (uv.x) * img.size.x;
	float fv = (uv.y) * img.size.y;
	fu = fabs(fu);
	fv = fabs(fv);
	int	u[4];
	int v[4];
	u[0] = u[2] = CLAMP((int)fu % img.size.x, 0, img.size.x);
	v[0] = v[1] = CLAMP((int)fv % img.size.y, 0, img.size.y);
	u[1] = u[3] = CLAMP((u[0] + 1) % img.size.x, 0, img.size.x);
	v[2] = v[3] = CLAMP((v[0] + 1) % img.size.y, 0, img.size.y);
	fu = fu - floorf(fu);
	fv = fv - floorf(fv);
	float weight[4];
	weight[0] = ((1 - fu) * (1 - fv));
	weight[1] = (fu * (1 - fv));
	weight[2] = ((1 - fu) * fv);
	weight[3] = (fu *  fv);
	int i = 0;
	while (i < 4)
	{
		pixel = img.pixels + (v[i] * img.sizeline + u[i] * img.opp);
		if (img.opp > 2)
		{
			color.x += (pixel[2] / 255.f) * weight[i];
			color.y += (pixel[1] / 255.f) * weight[i];
			color.z += (pixel[0] / 255.f) * weight[i];

		}
		else if (img.opp == 1)
			color.x = color.y = color.z += (pixel[0] / 255.f) * weight[i];
		i++;
	}
	return (color);
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

VEC3	sample_normal_map(void *normal_map, VEC2 uv, MAT3 tbn)
{
	VEC3	tnorm = sample_texture_filtered(normal_map, uv);
	tnorm = vec3_sub(vec3_scale(tnorm, 2), new_vec3(1, 1, 1));
	tnorm.x *= -1;
	tnorm.y *= -1;
	return (vec3_normalize(mat3_mult_vec3(tbn,
			vec3_normalize(tnorm))));
}
