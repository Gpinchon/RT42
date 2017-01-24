/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtllib3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:20:02 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/24 15:50:08 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*mtl_rock_sliced(ENGINE *e, SCENE *s)
{
	MATERIAL	*mtl;
	void		*f;

	if ((mtl = get_mtl_by_name(s, "rock_sliced")))
		return (mtl);
	f = e->framework;
	mtl = new_material(s, "rock_sliced");
	mtl->base_map = load_image_file(f,
		"res/rock_sliced/rock_sliced_base.bmp");
	mtl->metal_map = load_image_file(f,
		"res/rock_sliced/rock_sliced_metal.bmp");
	mtl->normal_map = load_image_file(f,
		"res/rock_sliced/rock_sliced_normal.bmp");
	mtl->rough_map = load_image_file(f,
		"res/rock_sliced/rock_sliced_rough.bmp");
	mtl->ao_map = load_image_file(f,
		"res/rock_sliced/rock_sliced_ao.bmp");
	mtl->height_map = load_image_file(f,
		"res/rock_sliced/rock_sliced_height.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.f;
	mtl->parallax = 0.1;
	return (mtl);
}

MATERIAL	*mtl_granite(ENGINE *e, SCENE *s)
{
	MATERIAL	*mtl;
	void		*f;

	if ((mtl = get_mtl_by_name(s, "granite")))
		return (mtl);
	f = e->framework;
	mtl = new_material(s, "granite");
	mtl->base_map = load_image_file(f,
		"res/granite/granite_base.bmp");
	mtl->metal_map = load_image_file(f,
		"res/granite/granite_metal.bmp");
	mtl->normal_map = load_image_file(f,
		"res/granite/granite_normal.bmp");
	mtl->rough_map = load_image_file(f,
		"res/granite/granite_rough.bmp");
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.5f;
	return (mtl);
}

MATERIAL	*mtl_light(ENGINE *engine, SCENE *scene)
{
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, "light")))
		return (mtl);
	mtl = new_material(scene, "light");
	mtl->refraction = 1.f;
	mtl->emitting.power = 1.f;
	mtl->emitting.attenuation = 0.002f;
	mtl->emitting.falloff = 5.f;
	mtl->emitting.color = new_vec3(1, 1, 1);
	mtl->emitting.type = POINT;
	return (mtl);
	(void)engine;
}
