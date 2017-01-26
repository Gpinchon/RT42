/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:01:53 by mbarbari          #+#    #+#             */
/*   Updated: 2017/01/26 19:10:41 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

unsigned long		djb2(const char *str)
{
	unsigned long	hash;
	int				c;
	int				i;

	hash = 5381;
	i = 0;
	while (str[i] && (c = str[i]))
	{
		hash = ((hash << 5) + hash) + c;
		++i;
	}
	return (hash);
}

unsigned long		*key_primitive(void)
{
	unsigned long	key_primitive[20];

	key_primitive[0] = djb2("SPHERE");
	key_primitive[1] = djb2("PLANE");
	key_primitive[2] = djb2("CYLINDER");
	key_primitive[3] = djb2("CONE");
	key_primitive[4] = djb2("TRIANGLE");
	key_primitive[5] = 0;
	return (key_primitive);
}

void				*fct_primitive(void)
{
	void	*fct_primitive[20];

	fct_primitive[0] = &new_sphere;
	fct_primitive[1] = &new_plane;
	fct_primitive[2] = &new_cylinder;
	fct_primitive[3] = &new_cone;
	fct_primitive[4] = &new_triangle;
}

	//if (ft_strequ(json_get(val.data.obj, "type").data.s, "SPHERE"))
	//	new_sphere(val, &data[idx]);
static void		fill_primitive(t_value val, int id, void *obj)
{
	static unsigned long	key_prim[] = key_primitive();
	static void				fct_prim[] = fct_primitive();
	t_value					arr;
	int						i;

	i = 0;
	arr = json_get(val.data.obj, "primitives");
	while(key_prim[i] != 0)
	{
		if (key_prim[i] == djb2(json_get(arr.data.obj, "type").data.s))
		{
			*obj-> = fct_prim[i](json_get(arr.data.obj, "data"));
			break ;
		}
	}
}

void		fill_primitive(ENGINE *engine, SCENE *scene)
{
	RTPRIMITIVE		*prim;

	prim = new_rtprim(scene);
}

void		create_scene(t_value val, t_env *env)
{
	t_value		primitives;
	RTPRIMITIVE	*prim;

	primitive = json_get(json_get(json_get(val.data.obj, "scene"),
				"primitives");
	json_foreach_arr(primitive.data.arr, &fill_arr, prim);
	env->arr[json_arr_length(
			json_get(val.data.obj, "scene").data.arr)].type = def;
	env->depth = (int)json_get(val.data.obj, "depth").data.number;
	env->sampling = (int)json_get(val.data.obj, "sampling").data.number;
}
