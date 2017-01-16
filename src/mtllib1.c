/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtllib1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:13:31 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/16 14:16:11 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*mtl_stained_glass(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "stained_glass")))
		return (m);
	m = new_material(s, "stained_glass");
	m->base_map = load_image_file(f, "res/stained_glass/stained_glass_base.bmp");
	m->metal_map = load_image_file(f, "res/stained_glass/stained_glass_metal.bmp");
	m->normal_map = load_image_file(f, "res/stained_glass/stained_glass_normal.bmp");
	m->height_map = load_image_file(f, "res/stained_glass/stained_glass_height.bmp");
	m->alpha_map = load_image_file(f, "res/stained_glass/stained_glass_alpha.bmp");
	m->parallax = 0.01;
	m->refraction = 1.52f;
	m->refraction_color = (VEC3){1, 1, 1};
	m->uv_scale = (VEC2){1, 1};
	m->roughness = 0.03;
	m->metalness = 0.5;
	m->alpha = 0.05;
	return (m);
}

MATERIAL	*mtl_metal_floor(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "metal_floor")))
		return (m);
	m = new_material(s, "metal_floor");
	m->base_map = load_image_file(f, "res/metal_floor/metal_floor_base.bmp");
	m->metal_map = load_image_file(f, "res/metal_floor/metal_floor_metal.bmp");
	m->normal_map = load_image_file(f, "res/metal_floor/metal_floor_normal.bmp");
	m->height_map = load_image_file(f, "res/metal_floor/metal_floor_height.bmp");
	m->rough_map = load_image_file(f, "res/metal_floor/metal_floor_rough.bmp");
	m->ao_map = load_image_file(f, "res/metal_floor/metal_floor_ao.bmp");
	m->parallax = 0.1;
	m->refraction = 1.5f;
	m->refraction_color = (VEC3){1, 1, 1};
	m->uv_scale = (VEC2){2, 2};
	m->roughness = 0.03;
	m->metalness = 0.5;
	m->alpha = 0.05;
	return (m);
}

MATERIAL	*mtl_rock_waterworn(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "rock_waterworn")))
		return (m);
	m = new_material(s, "rock_waterworn");
	m->base_map = load_image_file(f, "res/rock_waterworn/rock_waterworn_base.bmp");
	m->metal_map = load_image_file(f, "res/rock_waterworn/rock_waterworn_metal.bmp");
	m->normal_map = load_image_file(f, "res/rock_waterworn/rock_waterworn_normal.bmp");
	m->height_map = load_image_file(f, "res/rock_waterworn/rock_waterworn_height.bmp");
	m->rough_map = load_image_file(f, "res/rock_waterworn/rock_waterworn_rough.bmp");
	m->ao_map = load_image_file(f, "res/rock_waterworn/rock_waterworn_ao.bmp");
	m->parallax = 0.1;
	m->refraction = 1.5f;
	m->uv_scale = (VEC2){1, 1};
	return (m);
}

MATERIAL	*mtl_rusted_metal(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "rusted_metal")))
		return (m);
	m = new_material(s, "rusted_metal");
	m->base_map = load_image_file(f, "res/rusted_metal/rusted_metal_base.bmp");
	m->metal_map = load_image_file(f, "res/rusted_metal/rusted_metal_metal.bmp");
	m->normal_map = load_image_file(f, "res/rusted_metal/rusted_metal_normal.bmp");
	m->rough_map = load_image_file(f, "res/rusted_metal/rusted_metal_rough.bmp");
	m->uv_scale = (VEC2){1, 1};
	m->refraction = 1.4906f;
	return (m);
}

MATERIAL	*mtl_brick(ENGINE *e, SCENE *s)
{
	MATERIAL	*m;
	void		*f;

	f = e->framework;
	if ((m = get_mtl_by_name(s, "brick")))
		return (m);
	m = new_material(s, "brick");
	m->base_map = load_image_file(f, "res/brick/brick_base.bmp");
	m->metal_map = load_image_file(f, "res/brick/brick_metal.bmp");
	m->normal_map = load_image_file(f, "res/brick/brick_normal.bmp");
	m->rough_map = load_image_file(f, "res/brick/brick_rough.bmp");
	m->ao_map = load_image_file(f, "res/brick/brick_ao.bmp");
	m->height_map = load_image_file(f, "res/brick/brick_height.bmp");
	m->uv_scale = (VEC2){5, 5};
	m->refraction = 1.f;
	m->parallax = 0.1;
	return (m);
}