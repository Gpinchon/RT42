/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:01:53 by mbarbari          #+#    #+#             */
/*   Updated: 2017/01/27 17:29:13 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

typedef struct s_objprim t_objprim;
typedef struct e_typeargs t_typeargs;

enum			e_typeargs
{
	args0 = 0x00,
	args1 = 0x01,
	args2 = 0x02,
	args3 = 0x03,
	args4 = 0x04
};

struct			s_objprim
{
	void		*fct;
	e_typeargs	args;
};


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

void			set_fct_primitive(val, t_objprim prim)
{
	if (prim.args == args1)
		return (prim.fct(json_get(val.data.obj, "radius").data.number));
	else if (prim.args == args2)
		return (prim.fct(json_get(val.data.obj, "radius").data.number,
					json_get(val.data.obj, "size").data.number));
	else if (prim.args == args4)
		return (prim.fct(	get_vec3_json(json_get(val.data.obj, "a").data.number),
							get_vec3_json(json_get(val.data.obj, "b").data.number),
							get_vec3_json(json_get(val.data.obj, "c").data.number));
	return (prim.fct());
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

t_objprim			fct_prim(int id)
{
	static t_objprim	fct_primitive[20];
	static int			isinit = 0;

	if (isinit == 0)
	{
		fct_primitive[0] = (t_objprim) {&new_sphere, args1};
		fct_primitive[1] = (t_objprim) {&new_plane, args0};
		fct_primitive[2] = (t_objprim) {&new_cylinder, args2};
		fct_primitive[3] = (t_objprim) {&new_cone, args2};
		fct_primitive[4] = (t_objprim) {&new_triangle, argsdef};
		fct_primitive[5] = (t_objprim) {&new_disc, args1};
		fct_primitive[6] = (t_objprim) {&new_cylinder, args1};
		++isinit;
	}
	return (id < 0 ? NULL : fct_primitive[id]);
}

void		fill_camera(t_value val, int id, ENGINE *engine)
{
	t_json		*json;
	SCENE		*scene;

	scene = engine->scene;
	json = val.data.obj;
	scene->active_camera = new_camera(scene, json_get(json, "fov").data.number,
			json_get(json, "znear").data.number,
			json_get(json, "zfar").data.number);
	json = json_get(json, "transform");
	scene->active_camera->transform = new_rttransform(scene,
				get_vector3_from_json(json_get(json, "position")),
				get_vector3_from_json(json_get(json, "rotation")),
				get_vector3_from_json(json_get(json, "scaling")));
	json = json_get(json, "target");
	scene->active_camera->transform->target = new_rttransform(scene,
				get_vector3_from_json(json_get(json, "position")),
				vec3_normalize(get_vector3_from_json(json_get(json, "rotation"))),
				get_vector3_from_json(json_get(json, "scaling")));
	json = val.data.obj;
	scene->bloom_threshold = json_get(json, "bloom_threshold");
	scene->bloom_intensity = json_get(json, "bloom_intensity");
	scene->bloom_radius = json_get(json, "bloom_radius");
}

void		fill_map(t_value val, ENGINE *engine)
{
	MATERIAL				*mtl;
	t_json					*json;
	void					*fmk;

	mtl = engine.materials;
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
				vec3_normalize(get_vec3_json(json_get(arr.data.obj, "rotation"))),
				get_vec3_json(json_get(arr.data.obj, "scaling")));
		p->material = get_mtl_by_name(scene, json_get(val.data.obj, "material").data.s);
	}
}

ENGINE		*create_engine(t_value engin)
{
}

void		create_scene(t_value val, ENGINE *engine)
{
	t_value		scene;
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
