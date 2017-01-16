/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:09:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/16 14:39:01 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*get_mtl_by_name(SCENE *s, char *n)
{
	LINK		*link;

	link = s->materials;
	while (link)
	{
		if (!strcmp(((MATERIAL*)ezlink_get_data(link))->name, n))
			break ;
		link = link->next;
	}
	return (link ? ezlink_get_data(link) : NULL);
}

MATERIAL	*new_material(SCENE *s, char *n)
{
	LINK		*nl;
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, n)))
		return (mtl);
	if (!s->materials)
		nl = s->materials = new_ezlink(other, 1, sizeof(MATERIAL));
	else
	{
		nl = new_ezlink(other, 1, sizeof(MATERIAL));
		ezlink_append(s->materials, nl);
	}
	mtl = ezlink_get_data(nl);
	mtl->name = strcpy(malloc(sizeof(char) * strlen(n)), n);
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.f;
	mtl->alpha = 1;
	mtl->parallax = 0.05;
	return (ezlink_get_data(nl));
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
