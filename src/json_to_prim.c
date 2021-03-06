/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_prim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:16:20 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/13 18:52:12 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"
#include "parser.h"

int			get_idfct(unsigned long *key, unsigned long val)
{
	int			i;

	i = -1;
	while (key[++i] != 0)
		if (key[i] == val)
			return (i);
	return (-1);
}

PRIMITIVE	create_primitive(t_value v, t_objprim prim)
{
	if (prim.args == args1)
		return (((t_cb_1)prim.fct)(json_get(v.data.obj,
			"radius").data.number));
	else if (prim.args == args2)
		return (((t_cb_2)prim.fct)(json_get(v.data.obj, "radius").data.number,
					json_get(v.data.obj, "size").data.number));
	else if (prim.args == args4)
		return (((t_cb_3)prim.fct)(get_vec3_json(json_get(v.data.obj, "a")),
							get_vec3_json(json_get(v.data.obj, "b")),
							get_vec3_json(json_get(v.data.obj, "c"))));
	else
		return (((t_cb_0)prim.fct)());
}

int			key_primitive(unsigned long id)
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
		key_primitive[7] = 0;
		++isinit;
	}
	return (id == 0 ? -1 : get_idfct(key_primitive, id));
}

t_objprim	get_fct_primitive(int id)
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
		fct_primitive[6] = (t_objprim) {&new_cylinder, args2};
		++isinit;
	}
	return (id < 0 ? fct_primitive[19] : fct_primitive[id]);
}
