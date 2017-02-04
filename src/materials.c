/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:09:17 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/04 20:17:11 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/*
** Why not LINK instead of t_link ? Because norminette -_-
*/

MATERIAL	*get_mtl_by_name(SCENE *s, char *n)
{
	t_ezlink	*link;

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
	t_ezlink	*nl;
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(s, n)))
		return (mtl);
	if (!s->materials)
	{
		s->materials = new_ezlink(other, 1, sizeof(MATERIAL));
		nl = s->materials;
	}
	else
	{
		nl = new_ezlink(other, 1, sizeof(MATERIAL));
		ezlink_append(s->materials, nl);
	}
	mtl = ezlink_get_data(nl);
	mtl->name = strcpy(ezmemalloc(sizeof(char) * (strlen(n) + 1)), n);
	mtl->uv_scale = (VEC2){1, 1};
	mtl->refraction = 1.f;
	mtl->alpha = 1;
	mtl->parallax = 0.05;
	return (mtl);
}

void		get_ret_mtl(CAST_RETURN *ret)
{
	VEC2		uv;

	uv = ret->uv;
	if (ret->mtl.height_map)
	{
		ret->uv = sample_height_map(ret->mtl.height_map, ret);
		uv = ret->uv;
	}
	if (ret->mtl.normal_map)
		ret->intersect.normal = sample_normal_map(ret->mtl.normal_map, ret);
	if (ret->mtl.base_map)
	{
		ret->mtl.base_color = sample_texture_filtered(ret->mtl.base_map, uv);
		ret->mtl.reflection_color = ret->mtl.base_color;
	}
	if (ret->mtl.rough_map)
		ret->mtl.roughness = sample_texture_filtered(ret->mtl.rough_map, uv).x;
	if (ret->mtl.metal_map)
		ret->mtl.metalness = sample_texture_filtered(ret->mtl.metal_map, uv).x;
	if (ret->mtl.alpha_map)
		ret->mtl.alpha = sample_texture_filtered(ret->mtl.alpha_map, uv).x;
	if (ret->mtl.ao_map)
		ret->mtl.base_color = vec3_mult(ret->mtl.base_color,
			sample_texture_filtered(ret->mtl.ao_map, uv));
	if (ret->mtl.alpha == 1)
	{
		ret->intersect.position = vec3_add(ret->intersect.position,
			vec3_scale(ret->intersect.normal,
				sample_texture_filtered(ret->mtl.height_map, uv).x * ret->mtl.parallax));
		ret->intersect.distance[0] = vec3_distance(ret->ray.origin, ret->intersect.position);
	}
}
