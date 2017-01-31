/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:01:53 by mbarbari          #+#    #+#             */
/*   Updated: 2017/01/31 18:23:31 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"
#include "parser.h"

unsigned long		djb2(const char *str)
{
	unsigned long	hash;
	int				c;
	int				i;

	hash = 5381;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && (c = str[i]))
	{
		hash = ((hash << 5) + hash) + c;
		++i;
	}
	return (hash);
}

int					get_idfct(unsigned long *key, unsigned long val)
{
	int			i;

	i = -1;
	while (key[++i] != 0)
		if (key[i] == val)
			return (i);
	return (-1);
}


PRIMITIVE			create_primitive(t_value val, t_objprim prim)
{
	if (prim.args == args1)
		return (((cb_1)prim.fct)(json_get(val.data.obj, "radius").data.number));
	else if (prim.args == args2)
		return (((cb_2)prim.fct)(json_get(val.data.obj, "radius").data.number,
					json_get(val.data.obj, "size").data.number));
	else if (prim.args == args4)
		return (((cb_3)prim.fct)(	get_vec3_json(json_get(val.data.obj, "a")),
							get_vec3_json(json_get(val.data.obj, "b")),
							get_vec3_json(json_get(val.data.obj, "c"))));
	return (((cb_0)prim.fct)());
}

int				key_primitive(unsigned long id)
{
	static unsigned long	key_primitive[20];
	static int				isinit = 0;

	if (isinit == 0)
	{
		key_primitive[0] = djb2("SPHERE");
		key_primitive[1] = djb2("PLANE");
		key_primitive[2] = djb2("CYLINDER");
		key_primitive[3] = djb2("CONE");
		key_primitive[4] = djb2("TRIANGLE");
		key_primitive[5] = djb2("DISC");
		key_primitive[6] = djb2("CAPPED_CYLINDER");
		key_primitive[5] = 0;
		++isinit;
	}
	return (id == 0 ? -1 : get_idfct(key_primitive, id));
}

t_objprim			get_fct_primitive(int id)
{
	static t_objprim	fct_primitive[20];
	static int			isinit = 0;

	if (isinit == 0)
	{
		bzero(fct_primitive, sizeof(t_objprim) * 20);
		fct_primitive[0] = (t_objprim) {&new_sphere, args1};
		fct_primitive[1] = (t_objprim) {&new_plane, args0};
		fct_primitive[2] = (t_objprim) {&new_cylinder, args2};
		fct_primitive[3] = (t_objprim) {&new_cone, args2};
		fct_primitive[4] = (t_objprim) {&new_triangle, args4};
		fct_primitive[5] = (t_objprim) {&new_disc, args1};
		fct_primitive[6] = (t_objprim) {&new_cylinder, args1};
		++isinit;
	}
	return (id < 0 ? fct_primitive[19] : fct_primitive[id]);
}

void		create_scene(t_value val, ENGINE *engine)
{
	t_value		scene;
	t_value		camera;
	t_value		materials;
	t_value		primitives;

	(void)engine;
	scene = json_get(val.data.obj, "scene");
	camera = json_get(scene.data.obj, "camera");
	materials = json_get(scene.data.obj, "materials");
	primitives = json_get(scene.data.obj, "primitives");
	fill_camera(camera, &engine->scene);
	json_foreach_arr(materials.data.arr, &fill_materials, engine);
	json_foreach_arr(primitives.data.arr, &fill_primitive, engine);
}
