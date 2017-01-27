/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtllib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:11:48 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/27 14:51:23 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*mtl_aquamarine(ENGINE *m, SCENE *s)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, "aquamarine")))
		return (mtl);
	mtl = new_material(s, "aquamarine");
	mtl->refraction = 1.59f * 2.f;
	mtl->base_color = (VEC3){0.419607843, 0.792156863, 0.88627451};
	mtl->refraction_color = (VEC3){0.419607843, 0.792156863, 0.88627451};
	mtl->reflection_color = (VEC3){1, 1, 1};
	mtl->normal_map = load_image_file(m->framework, "res/scratch.bmp");
	mtl->uv_scale = (VEC2){3, 3};
	mtl->roughness = 0.03;
	mtl->metalness = 0.5;
	mtl->alpha = 0.05;
	return (mtl);
}

MATERIAL	*mtl_water(ENGINE *m, SCENE *s)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, "water")))
		return (mtl);
	mtl = new_material(s, "water");
	mtl->refraction = 1.33f;
	mtl->base_color = (VEC3){0.05, 0.05, 0.1};
	mtl->refraction_color = (VEC3){0.9, 0.9, 1};
	mtl->reflection_color = (VEC3){1, 1, 1};
	mtl->normal_map = load_image_file(m->framework,
		"res/water/water_normal.bmp");
	mtl->height_map = load_image_file(m->framework,
		"res/water/water_height.bmp");
	mtl->uv_scale = (VEC2){4, 4};
	mtl->roughness = 0.05;
	mtl->metalness = 0.5;
	mtl->alpha = 0.05;
	mtl->parallax = 0.1;
	return (mtl);
}

MATERIAL	*mtl_scuffed_plastic_red(ENGINE *m, SCENE *s)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, "scuffed_plastic_red")))
		return (mtl);
	mtl = new_material(s, "scuffed_plastic_red");
	mtl->base_map = load_image_file(m->framework,
		"res/scuffed_plastic/scuffed_plastic_red_base.bmp");
	mtl->metal_map = load_image_file(m->framework,
		"res/scuffed_plastic/scuffed_plastic_metal.bmp");
	mtl->normal_map = load_image_file(m->framework,
		"res/scuffed_plastic/scuffed_plastic_normal.bmp");
	mtl->rough_map = load_image_file(m->framework,
		"res/scuffed_plastic/scuffed_plastic_rough.bmp");
	mtl->ao_map = load_image_file(m->framework,
		"res/scuffed_plastic/scuffed_plastic_ao.bmp");
	mtl->refraction = 1.4906f;
	return (mtl);
}

MATERIAL	*mtl_scuffed_aluminium(ENGINE *m, SCENE *s)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, "scuffed_aluminium")))
		return (mtl);
	mtl = new_material(s, "scuffed_aluminium");
	mtl->base_map = load_image_file(m->framework,
		"res/scuffed_aluminium/scuffed_aluminium_base.bmp");
	mtl->metal_map = load_image_file(m->framework,
		"res/scuffed_aluminium/scuffed_aluminium_metal.bmp");
	mtl->normal_map = load_image_file(m->framework,
		"res/scuffed_aluminium/scuffed_aluminium_normal.bmp");
	mtl->rough_map = load_image_file(m->framework,
		"res/scuffed_aluminium/scuffed_aluminium_rough.bmp");
	mtl->refraction = 1.59f;
	return (mtl);
}

MATERIAL	*mtl_greasy_metal(ENGINE *m, SCENE *s)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, "greasy_metal")))
		return (mtl);
	mtl = new_material(s, "greasy_metal");
	mtl->base_map = load_image_file(m->framework,
		"res/greasy_metal/greasy_metal_base.bmp");
	mtl->metal_map = load_image_file(m->framework,
		"res/greasy_metal/greasy_metal_metal.bmp");
	mtl->normal_map = load_image_file(m->framework,
		"res/greasy_metal/greasy_metal_normal.bmp");
	mtl->rough_map = load_image_file(m->framework,
		"res/greasy_metal/greasy_metal_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.59f;
	return (mtl);
}
