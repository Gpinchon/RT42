/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 16:09:37 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/13 16:10:23 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"
#include "parser.h"

static inline void	get_vectors(SCENE *scene, t_json_arr *arr[3],
	RTTRANSFORM *t, MATERIAL *m)
{
	t_rtprim	*p;

	while (arr[0])
	{
		arr[1] = arr[0]->next;
		arr[2] = arr[1] ? arr[1]->next : NULL;
		if (!arr[0] || !arr[1] || !arr[2])
			return ;
		p = new_rtprim(scene);
		p->prim = new_triangle(get_vec3_json(arr[0]->value),
			get_vec3_json(arr[1]->value), get_vec3_json(arr[2]->value));
		p->transform = t;
		p->material = m;
		arr[0] = arr[2]->next;
	}
}

void				fill_mesh(t_value v, int i, void *obj)
{
	ENGINE					*engine;
	t_json_arr				*arr[3];
	t_json					*j;
	RTTRANSFORM				*t;
	MATERIAL				*m;

	(void)i;
	if (djb2(json_get(v.data.obj, "type").data.s) != djb2("MESH"))
		return ;
	engine = (ENGINE *)obj;
	arr[0] = json_get(v.data.obj, "vectors").data.arr;
	j = json_get(v.data.obj, "transform").data.obj;
	t = new_rttransform(&engine->scene,
		get_vec3_json(json_get(j, "position")),
		get_vec3_json(json_get(j, "rotation")),
		get_vec3_json(json_get(j, "scaling")));
	transform_update(&t->current);
	m = get_mtl_by_name(&engine->scene,
		json_get(v.data.obj, "material").data.s);
	get_vectors(&engine->scene, arr, t, m);
}
