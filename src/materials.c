/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:09:17 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/06 00:20:30 by gpinchon         ###   ########.fr       */
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
	mtl->refraction_color = (VEC3){0, 1, 0.5};
	mtl->reflection_color = (VEC3){1, 1, 1};
	mtl->normal_map = load_image_file(engine->framework, "res/rock.bmp");
	mtl->uv_scale = (VEC2){3, 3};
	mtl->roughness = 0.3;
	mtl->metalness = 0.5;
	mtl->alpha = 0.8;
	return (mtl);
}

MATERIAL	*mtl_water(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "water")))
		return (mtl);
	mtl = new_material(scene, "water");
	mtl->refraction = 1.33f;
	mtl->base_color = (VEC3){0.0, 0.0, 0.01};
	mtl->refraction_color = (VEC3){0.9, 0.9, 1};
	mtl->reflection_color = (VEC3){1, 1, 1};
	mtl->normal_map = load_image_file(engine->framework, "res/water_normal.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->roughness = 0.03;
	mtl->metalness = 1;
	mtl->alpha = 0.5;
	return (mtl);
}

MATERIAL	*mtl_greasy_metal(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "greasy_metal")))
		return (mtl);
	mtl = new_material(scene, "greasy_metal");
	mtl->base_map = load_image_file(engine->framework, "res/greasy_metal_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/greasy_metal_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/greasy_metal_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/greasy_metal_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.1f;
	return (mtl);
}

MATERIAL	*mtl_rusted_metal(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "rusted_metal")))
		return (mtl);
	mtl = new_material(scene, "rusted_metal");
	mtl->base_map = load_image_file(engine->framework, "res/rusted_metal_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/rusted_metal_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/rusted_metal_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/rusted_metal_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.1f;
	return (mtl);
}

MATERIAL	*mtl_copper_rock(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "copper_rock")))
		return (mtl);
	mtl = new_material(scene, "copper_rock");
	mtl->base_map = load_image_file(engine->framework, "res/copper_rock_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/copper_rock_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/copper_rock_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/copper_rock_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.1f;
	return (mtl);
}

MATERIAL	*mtl_granite(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "granite")))
		return (mtl);
	mtl = new_material(scene, "granite");
	mtl->base_map = load_image_file(engine->framework, "res/granite_base.bmp");
	mtl->metal_map = load_image_file(engine->framework, "res/granite_metal.bmp");
	mtl->normal_map = load_image_file(engine->framework, "res/granite_normal.bmp");
	mtl->rough_map = load_image_file(engine->framework, "res/granite_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.5f;
	return (mtl);
}
