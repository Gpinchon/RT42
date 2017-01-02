/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:09:17 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/31 01:33:15 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*get_mtl_by_name(SCENE *scene, char *name)
{
	LINK		*link;

	link = scene->materials;
	while (link)
	{
		if (!strcmp(((MATERIAL*)ezlink_get_data(link))->name, name))
			break ;
		link = link->next;
	}
	return (link ? ezlink_get_data(link) : NULL);
}

MATERIAL	*mtl_aquamarine(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "aquamarine")))
		return (mtl);
	mtl = new_material(scene, "aquamarine");
	mtl->refraction = 1.59f * 2.f;
	mtl->base_color = (VEC3){0.419607843, 0.792156863, 0.88627451};
	mtl->refraction_color = (VEC3){0.419607843, 0.792156863, 0.88627451};
	mtl->reflection_color = (VEC3){1, 1, 1};
	mtl->normal_map = load_image_file(engine->framework, "res/scratch.bmp");
	mtl->uv_scale = (VEC2){3, 3};
	mtl->roughness = 0.03;
	mtl->metalness = 0.5;
	mtl->alpha = 0.1;
	return (mtl);
	(void)engine;
}

MATERIAL	*mtl_water(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "water")))
		return (mtl);
	mtl = new_material(scene, "water");
	mtl->refraction = 1.33f;
	mtl->base_color = (VEC3){0.05, 0.05, 0.1};
	mtl->refraction_color = (VEC3){0.9, 0.9, 1};
	mtl->reflection_color = (VEC3){1, 1, 1};
	mtl->normal_map = load_image_file(engine->framework, "res/water/water_normal.bmp");
	mtl->uv_scale = (VEC2){2, 2};
	mtl->roughness = 0.05;
	mtl->metalness = 0.5;
	mtl->alpha = 0.05;
	return (mtl);
}

MATERIAL	*mtl_scuffed_plastic_red(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "scuffed_plastic_red")))
		return (mtl);
	mtl = new_material(scene, "scuffed_plastic_red");
	mtl->base_map = load_image_file(engine->framework, "res/scuffed_plastic/scuffed_plastic_red_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/scuffed_plastic/scuffed_plastic_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/scuffed_plastic/scuffed_plastic_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/scuffed_plastic/scuffed_plastic_rough.bmp");
	mtl->ao_map = load_image_file(engine->framework, "res/scuffed_plastic/scuffed_plastic_ao.bmp");
	mtl->refraction = 1.4906f;
	return (mtl);
}

MATERIAL	*mtl_scuffed_aluminium(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "scuffed_aluminium")))
		return (mtl);
	mtl = new_material(scene, "scuffed_aluminium");
	mtl->base_map = load_image_file(engine->framework, "res/scuffed_aluminium/scuffed_aluminium_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/scuffed_aluminium/scuffed_aluminium_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/scuffed_aluminium/scuffed_aluminium_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/scuffed_aluminium/scuffed_aluminium_rough.bmp");
	mtl->refraction = 1.59f;
	return (mtl);
}

MATERIAL	*mtl_greasy_metal(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "greasy_metal")))
		return (mtl);
	mtl = new_material(scene, "greasy_metal");
	mtl->base_map = load_image_file(engine->framework, "res/greasy_metal/greasy_metal_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/greasy_metal/greasy_metal_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/greasy_metal/greasy_metal_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/greasy_metal/greasy_metal_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.59f;
	return (mtl);
}

MATERIAL	*mtl_rusted_metal(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "rusted_metal")))
		return (mtl);
	mtl = new_material(scene, "rusted_metal");
	mtl->base_map = load_image_file(engine->framework, "res/rusted_metal/rusted_metal_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/rusted_metal/rusted_metal_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/rusted_metal/rusted_metal_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/rusted_metal/rusted_metal_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.4906f;
	return (mtl);
}

MATERIAL	*mtl_brick(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "brick")))
		return (mtl);
	mtl = new_material(scene, "brick");
	mtl->base_map = load_image_file(engine->framework, "res/brick/brick_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/brick/brick_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/brick/brick_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/brick/brick_rough.bmp");
	mtl->ao_map = load_image_file(engine->framework, "res/brick/brick_ao.bmp");
	mtl->height_map = load_image_file(engine->framework, "res/brick/brick_height.bmp");
	mtl->uv_scale = (VEC2){5, 5};
	mtl->refraction = 1.f;
	mtl->parallax = 0.1;
	return (mtl);
}

MATERIAL	*mtl_octostone(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "octostone")))
		return (mtl);
	mtl = new_material(scene, "octostone");
	mtl->base_map = load_image_file(engine->framework, "res/octostone/octostone_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/octostone/octostone_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/octostone/octostone_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/octostone/octostone_rough.bmp");
	mtl->ao_map = load_image_file(engine->framework, "res/octostone/octostone_ao.bmp");
	mtl->height_map = load_image_file(engine->framework, "res/octostone/octostone_height.bmp");
	mtl->uv_scale = (VEC2){5, 5};
	mtl->refraction = 1.f;
	return (mtl);
}

MATERIAL	*mtl_harshbricks(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "harshbricks")))
		return (mtl);
	mtl = new_material(scene, "harshbricks");
	mtl->base_map = load_image_file(engine->framework, "res/harshbricks/harshbricks_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/harshbricks/harshbricks_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/harshbricks/harshbricks_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/harshbricks/harshbricks_rough.bmp");
	mtl->ao_map = load_image_file(engine->framework, "res/harshbricks/harshbricks_ao.bmp");
	mtl->height_map = load_image_file(engine->framework, "res/harshbricks/harshbricks_height.bmp");
	mtl->uv_scale = (VEC2){5, 5};
	mtl->refraction = 1.1f;
	mtl->parallax = 0.1;
	return (mtl);
}

MATERIAL	*mtl_rock_copper(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "rock_copper")))
		return (mtl);
	mtl = new_material(scene, "rock_copper");
	mtl->base_map = load_image_file(engine->framework, "res/rock_copper/rock_copper_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/rock_copper/rock_copper_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/rock_copper/rock_copper_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/rock_copper/rock_copper_rough.bmp");
	mtl->ao_map = load_image_file(engine->framework, "res/rock_copper/rock_copper_ao.bmp");
	mtl->height_map = load_image_file(engine->framework, "res/rock_copper/rock_copper_height.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.1f;
	mtl->parallax = 0.1;
	return (mtl);
}

MATERIAL	*mtl_rock_sliced(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "rock_sliced")))
		return (mtl);
	mtl = new_material(scene, "rock_sliced");
	mtl->base_map = load_image_file(engine->framework, "res/rock_sliced/rock_sliced_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/rock_sliced/rock_sliced_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/rock_sliced/rock_sliced_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/rock_sliced/rock_sliced_rough.bmp");
	mtl->ao_map = load_image_file(engine->framework, "res/rock_sliced/rock_sliced_ao.bmp");
	mtl->height_map = load_image_file(engine->framework, "res/rock_sliced/rock_sliced_height.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.f;
	mtl->parallax = 0.1;
	return (mtl);
}

MATERIAL	*mtl_granite(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "granite")))
		return (mtl);
	mtl = new_material(scene, "granite");
	mtl->base_map = load_image_file(engine->framework, "res/granite/granite_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/granite/granite_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/granite/granite_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/granite/granite_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.5f;
	return (mtl);
}
