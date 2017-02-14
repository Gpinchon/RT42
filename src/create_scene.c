/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:01:53 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/14 19:10:48 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"
#include "parser.h"

static int		test_jsonclass(t_value val, const char *str)
{
	if (json_get(val.data.obj, (char *)str).error == TYPE_ERROR)
		return (1);
	return (0);
}

unsigned long	djb2(const char *str)
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

ENGINE			set_engine(t_value val)
{
	t_json			*json;
	t_engine_opt	options;

	json = json_get(val.data.obj, "engine").data.obj;
	options.max_refr = json_get(json, "max_refr").data.number;
	options.max_refl = json_get(json, "max_refl").data.number;
	options.area_sampling = json_get(json, "area_sampling").data.number;
	options.window_size.x = json_get(json, "window height").data.number;
	options.window_size.y = json_get(json, "window width").data.number;
	options.internal_size.x = json_get(json, "internal height").data.number;
	options.internal_size.y = json_get(json, "internal width").data.number;
	return (new_engine(options));
}

ENGINE			fill_scene(t_value val, t_value scene)
{
	ENGINE		engine;

	engine = set_engine(val);
	if (test_jsonclass(scene, "camera") == 0)
		fill_camera(json_get(scene.data.obj, "camera"), &engine.scene);
	if (test_jsonclass(scene, "materials") == 0)
		json_foreach_arr(json_get(scene.data.obj, "materials").data.arr,
				&fill_materials, &engine);
	if (test_jsonclass(scene, "primitives") == 0)
	{
		json_foreach_arr(json_get(scene.data.obj, "primitives").data.arr,
				&fill_primitive, &engine);
		json_foreach_arr(json_get(scene.data.obj, "primitives").data.arr,
				&fill_mesh, &engine);
	}
	if (test_jsonclass(scene, "lights") == 0)
		json_foreach_arr(json_get(scene.data.obj, "lights").data.arr,
				&fill_lights, &engine);
	return (engine);
}

ENGINE			create_scene(t_value v)
{
	if (test_jsonclass(v, "engine") == 1 || test_jsonclass(v, "scene") == 1)
	{
		write(1, "Engine or scene class in json file missing\n", 43);
		json_free(v);
		exit(0);
	}
	return (fill_scene(v, json_get(v.data.obj, "scene")));
}
