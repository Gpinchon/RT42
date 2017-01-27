/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:01:53 by mbarbari          #+#    #+#             */
/*   Updated: 2017/01/27 15:56:40 by mbarbari         ###   ########.fr       */
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
		key_primitive[5] = 0;
		++isinit;
	}
	return (id == 0 ? -1 : get_idfct(key_primitive, id));
}

void			*fct_prim(int id)
{
	static void	*fct_primitive[20];
	static int	isinit = 0;

	if (isinit == 0)
	{
		fct_primitive[0] = &new_sphere;
		fct_primitive[1] = &new_plane;
		fct_primitive[2] = &new_cylinder;
		fct_primitive[3] = &new_cone;
		fct_primitive[4] = &new_triangle;
		++isinit;
	}
	return (id < 0 ? NULL : fct_primitive[id]);
}

void		fill_camera(t_value val, int id, void *obj)
{
	SCENE		*scene;
	ENGINE		*engine;

	scene = (t_data *)obj->scene;
	engine = (t_data *)obj->engine;
	scene->active_camera = new_camera(scene, json_get(val.data.obj, "fov").data.number,
			json_get(val.data.obj, "znear").data.number,
			json_get(val.data.obj, "zfar").data.number);
	scene->active_camera->transform = new_rttransform(scene,
				get_vector3_from_json(json_get(arr.data.obj, "position")),
				get_vector3_from_json(json_get(arr.data.obj, "rotation")),
				get_vector3_from_json(json_get(arr.data.obj, "scaling")));
	scene->active_camera->transform->target = new_rttransform(scene,
				get_vector3_from_json(json_get(arr.data.obj, "position")),
				get_vector3_from_json(json_get(arr.data.obj, "rotation")),
				get_vector3_from_json(json_get(arr.data.obj, "scaling")));
	scene->bloom_threshold = json_get(arr.data.obj, "bloom_threshold");
	scene->bloom_intensity = json_get(arr.data.obj, "bloom_intensity");
	scene->bloom_radius = json_get(arr.data.obj, "bloom_radius");
}

void		fill_map(t_value val, ENGINE *engine, MATERIAL *mtl)
{
	t_json					*json;
	void					*fmk;

	json = arr.data.obj;
	fmk = engine->framework;
	mtl->normal_map = load_image_file(fmk, json_get(json, "normal_map").data.s);
	obj->height_map = load_image_file(fmk, json_get(json, "height_map").data.s);
	mtl->base_map = load_image_file(fmk, json_get(json, "base_map").data.s);
	mtl->metal_map = load_image_file(fmk, json_get(json, "metal_map").data.s);
	mtl->rough_map = load_image_file(fmk, json_get(json, "rough_map").data.s);
	mtl->ao_map = load_image_file(fmk, json_get(json, "ao_map").data.s);
}

void		fill_materials(t_value val, int id, void *obj)
{
	MATERIAL				*mat;
	SCENE					*scene;
	ENGINE					*engine;
	t_json					*json;

	scene = (t_data *)obj->scene;
	engine = (t_data *)obj->engine;
	json = arr.data.obj;
	mat = new_material(scene, json_get(json, "name").data.s);
	fill_map(val, engine, mat);
	mat->refraction = json_get(json, "refraction").data.number;
	mat->base_color = get_vec3_json(json_get(json, "base_color"));
	mat->refraction_color = get_vec3_json(json_get(json, "refraction_color"));
	mat->reflection_color = get_vec3_json(json_get(json, "reflection_color"));
	mat->uv_scale = new_vec2(json_get(json_get(json, "uv_scale"), "x").data.number,
							json_get(json_get(json, "uv_scale"), "y").data.number);
	mat->roughness = json_get(json, "roughness").data.number;
	mat->metalness = json_get(json, "metalness").data.number;
	mat->alpha = json_get(json, "alpha").data.number;
	mat->parallax = json_get(json, "parallax").data.number;
	mat->emitting.power = json_get(json, "emitting_power").data.number;
	mat->emitting.attenuation = json_get(json, "emitting_attenuation").data.number;
	mat->emitting.falloff = json_get(json, "emitting_falloff").data.number;
	mat->emitting.color = get_vec3_json(json_get(json, "emitting_color"));
	(t_data *)obj->materials = mat;
}

void		fill_lights(t_value val, int id, void *obj)
{
}

void		fill_primitive(t_value val, int id, void *obj)
{
	SCENE					*scene;
	ENGINE					*engine;
	RTPRIMITIVE				*p;
	void					*fct;
	t_value					arr;

	scene = (t_data *)obj->scene;
	engine = (t_data *)obj->engine;
	fct = fct_prim(key_prim(djb2(json_get(val.data.obj, "type").data.s)));
	if (fct != NULL)
	{
		p = new_rtprim(scene);
		p->prim = fct(val);
		arr = json_get(val.data.obj, "transform");
		p->transform = new_rttransform(scene,
				get_vec3_json(json_get(arr.data.obj, "position")),
				get_vec3_json(json_get(arr.data.obj, "rotation")),
				get_vec3_json(json_get(arr.data.obj, "scaling")));
		//fct = fct_mat(key_mat(djb2(json_get(val.data.obj, "material").data.s)));
		//if (fct != NULL)
		p->material = get_mtl_by_name(scene, json_get(val.data.obj, "material").data.s);
	}
}

void		create_engine(t_value engin)
{
}

void		create_scene(char *file, ENGINE *engine)
{
	t_value		camera;
	t_value		materials;
	t_value		primitives;

	scene = json_get(val.data.obj, "scene");
	camera = json_get(scene.data.obj, "camera");
	materials = json_get(scene.data.obj, "materials");
	primitives = json_get(scene.data.obj, "primitives");
	json_foreach_arr(camera.data.arr, &fill_camera, engine);
	json_foreach_arr(materials.data.arr, &fill_materials, engine);
	json_foreach_arr(primitive.data.arr, &fill_primitive, engine);
}
