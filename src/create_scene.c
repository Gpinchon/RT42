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
#include <sys/stat.h>

//int		file_is_modified(const char *path, time_t *oldtime, int i)
//{
//	int			testing;
//	struct stat	file_stat;
//	int			err;
//	int			ismodified;
//
//	testing = -1;
//	while ((err = stat(path, &file_stat)) < 0)
//	{
//		sleep(1);
//		if (++testing == 10)
//			exit(0);
//		if ((err = stat(path, &file_stat)) < 0)
//			dprintf("[FILE KO] : %s\n", path); //TODO: pas de printf
//		else
//			break ;
//	}
//	if (i == 1)
//		*oldtime = file_stat.st_mtime;
//	else
//	{
//		ismodified = file_stat.st_mtime > *oldtime;
//		*oldtime = file_stat.st_mtime;
//		return (ismodified);
//	}
//	return (0);
//}

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

ENGINE		set_engine(t_value val)
{
	t_json			*json;
	t_engine_opt	options;
	//t_point2		pt;

	json = json_get(val.data.obj, "engine").data.obj;
	options.max_refr = json_get(json, "max_refr").data.number;
	options.max_refl = json_get(json, "max_refl").data.number;
	options.area_sampling = json_get(json, "area_sampling").data.number;
	//pt.x = json_get(json, "window height").data.number;
	//pt.y = json_get(json, "window width").data.number;
	//options.window_size = (options.internal_size = pt);
	//pt.x = json_get(json, "internal height").data.number;
	//pt.y = json_get(json, "internal width").data.number;
	//options.internal_size = pt;
	options.window_size = options.internal_size = (t_point2){1024, 1024};
	return (new_engine(options));
}

ENGINE		create_scene(t_value val)
{
	ENGINE		engine;
	t_value		camera;
	t_value		materials;
	t_value		primitives;
	t_value		lights;

	engine = set_engine(val);
	camera = json_get(json_get(val.data.obj, "scene").data.obj, "camera");
	materials = json_get(json_get(val.data.obj, "scene").data.obj, "materials");
	primitives = json_get(json_get(val.data.obj, "scene").data.obj, "primitives");
	lights = json_get(json_get(val.data.obj, "scene").data.obj, "lights");
	fill_camera(camera, &engine.scene);
	json_foreach_arr(materials.data.arr, &fill_materials, &engine);
	json_foreach_arr(primitives.data.arr, &fill_primitive, &engine);
	json_foreach_arr(lights.data.arr, &fill_lights, &engine);
	return (engine);
}
