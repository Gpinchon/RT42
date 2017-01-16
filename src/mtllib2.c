/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtllib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:17:06 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/16 14:19:32 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*mtl_octostone(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "octostone")))
		return (m);
	m = new_material(s, "octostone");
	m->base_map = load_image_file(f, "res/octostone/octostone_base.bmp");
	m->metal_map = load_image_file(f, "res/octostone/octostone_metal.bmp");
	m->normal_map = load_image_file(f, "res/octostone/octostone_normal.bmp");
	m->rough_map = load_image_file(f, "res/octostone/octostone_rough.bmp");
	m->ao_map = load_image_file(f, "res/octostone/octostone_ao.bmp");
	m->height_map = load_image_file(f, "res/octostone/octostone_height.bmp");
	m->uv_scale = (VEC2){5, 5};
	m->refraction = 1.33f;
	m->parallax = 0.1;
	return (m);
}

MATERIAL	*mtl_skin(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "skin")))
		return (m);
	m = new_material(s, "skin");
	m->base_map = load_image_file(f, "res/skin/skin_base.bmp");
	m->normal_map = load_image_file(f, "res/skin/skin_normal.bmp");
	m->rough_map = load_image_file(f, "res/skin/skin_rough.bmp");
	m->ao_map = load_image_file(f, "res/skin/skin_ao.bmp");
	m->height_map = load_image_file(f, "res/skin/skin_height.bmp");
	m->uv_scale = (VEC2){5, 5};
	m->refraction = 1.33f;
	m->roughness = 0.5f;
	m->parallax = 0.1;
	return (m);
}

MATERIAL	*mtl_mirror(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	m = new_material(s, "mirror");
	m->base_color = (VEC3){0.1, 0.1, 0.1};
	m->reflection_color = (VEC3){1, 1, 1};
	m->refraction = 1.90f;
	m->roughness = 0;
	m->metalness = 1;
	m->alpha = 1;
	return (m);
	(void)e;
}

MATERIAL	*mtl_harshbricks(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "harshbricks")))
		return (m);
	m = new_material(s, "harshbricks");
	m->base_map = load_image_file(f, "res/harshbricks/harshbricks_base.bmp");
	m->metal_map = load_image_file(f, "res/harshbricks/harshbricks_metal.bmp");
	m->normal_map = load_image_file(f, "res/harshbricks/harshbricks_normal.bmp");
	m->rough_map = load_image_file(f, "res/harshbricks/harshbricks_rough.bmp");
	m->ao_map = load_image_file(f, "res/harshbricks/harshbricks_ao.bmp");
	m->height_map = load_image_file(f, "res/harshbricks/harshbricks_height.bmp");
	m->uv_scale = (VEC2){5, 5};
	m->refraction = 1.1f;
	m->parallax = 0.1;
	return (m);
}

MATERIAL	*mtl_rock_copper(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "rock_copper")))
		return (m);
	m = new_material(s, "rock_copper");
	m->base_map = load_image_file(f, "res/rock_copper/rock_copper_base.bmp");
	m->metal_map = load_image_file(f, "res/rock_copper/rock_copper_metal.bmp");
	m->normal_map = load_image_file(f, "res/rock_copper/rock_copper_normal.bmp");
	m->rough_map = load_image_file(f, "res/rock_copper/rock_copper_rough.bmp");
	m->ao_map = load_image_file(f, "res/rock_copper/rock_copper_ao.bmp");
	m->height_map = load_image_file(f, "res/rock_copper/rock_copper_height.bmp");
	m->uv_scale = (VEC2){1, 1};
	m->refraction = 1.1f;
	m->parallax = 0.1;
	return (m);
}
