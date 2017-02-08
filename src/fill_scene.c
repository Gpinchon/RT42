/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:14:10 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/08 18:27:11 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "scene.h"
#include "parser.h"

void		fill_camera(t_value val, void *obj)
{
	t_scene		*scene;
	t_json		*json;

	json = val.data.obj;
	scene = (SCENE*)obj;
	scene->active_camera = new_camera(scene,
			json_get(json, "fov").data.number,
			json_get(json, "znear").data.number,
			json_get(json, "zfar").data.number);
	json = json_get(json, "transform").data.obj;
	scene->active_camera->transform = new_rttransform(scene,
				get_vec3_json(json_get(json, "position")),
				get_vec3_json(json_get(json, "rotation")),
				get_vec3_json(json_get(json, "scaling")));
	json = json_get(val.data.obj, "target").data.obj;
	scene->active_camera->transform->target = new_rttransform(scene,
				get_vec3_json(json_get(json, "position")),
				vec3_normalize(get_vec3_json(json_get(json, "rotation"))),
				get_vec3_json(json_get(json, "scaling")));
	json = val.data.obj;
	scene->bloom_threshold = json_get(json, "bloom_threshold").data.number;
	scene->bloom_intensity = json_get(json, "bloom_intensity").data.number;
	scene->bloom_radius = json_get(json, "bloom_radius").data.number;
}

void		fill_map(t_value val, ENGINE *engine, MATERIAL *m)
{
	t_json					*json;
	void					*f;
	t_value					v;

	json = val.data.obj;
	f = engine->framework;
	v = json_get(json, "normal_map");
	m->normal_map = load_image_file(f, v.error == TYPE_ERROR ? NULL :
		v.data.s);
	v = json_get(json, "alpha_map");
	m->alpha_map = load_image_file(f, v.error == TYPE_ERROR ? NULL : v.data.s);
	v = json_get(json, "height_map");
	m->height_map = load_image_file(f, v.error == TYPE_ERROR ? NULL :
		v.data.s);
	v = json_get(json, "base_map");
	m->base_map = load_image_file(f, v.error == TYPE_ERROR ? NULL : v.data.s);
	v = json_get(json, "metal_map");
	m->metal_map = load_image_file(f, v.error == TYPE_ERROR ? NULL : v.data.s);
	v = json_get(json, "rough_map");
	m->rough_map = load_image_file(f, v.error == TYPE_ERROR ? NULL : v.data.s);
	v = json_get(json, "ao_map");
	m->ao_map = load_image_file(f, v.error == TYPE_ERROR ? NULL : v.data.s);
}

void		fill_materials(t_value val, int id, void *engine)
{
	MATERIAL		*m;
	t_json			*o;

	(void)id;
	o = val.data.obj;
	if ((get_mtl_by_name((SCENE *)&((ENGINE*)engine)->scene,
					json_get(o, "name").data.s)))
		return ;
	m = new_material((SCENE *)&((ENGINE*)engine)->scene,
			json_get(o, "name").data.s);
	fill_map(val, (ENGINE *)engine, m);
	m->refraction = json_get(o, "refraction").data.number;
	m->base_color = get_vec3_json(json_get(o, "base_color"));
	m->refraction_color = get_vec3_json(json_get(o, "refraction_color"));
	m->reflection_color = get_vec3_json(json_get(o, "reflection_color"));
	m->uv_scale = get_vec2_json(json_get(o, "uv_scale"));
	m->roughness = json_get(o, "roughness").data.number;
	m->metalness = json_get(o, "metalness").data.number;
	m->alpha = json_get(o, "alpha").data.number;
	m->parallax = json_get(o, "parallax").data.number;
	m->emitting.type = POINT;
	m->emitting.power = json_get(o, "emitting_power").data.number;
	m->emitting.attenuation = json_get(o, "emitting_attenuation").data.number;
	m->emitting.falloff = json_get(o, "emitting_falloff").data.number;
	m->emitting.color = get_vec3_json(json_get(o, "emitting_color"));
}

void		fill_lights(t_value val, int i, void *obj)
{
	ENGINE	*engine;
	t_light	*l;
	t_json	*json;

	(void)i;
	engine = obj;
	json = val.data.obj;
	l = new_light(&engine->scene, json_get(json, "type").data.number,
			get_vec3_json(json_get(json, "position")));
	l->color = get_vec3_json(json_get(json, "color"));
	l->cast_shadow = json_get(json, "cast_shadow").data.boolean;
	l->direction = get_vec3_json(json_get(json, "direction"));
	l->power = json_get(json, "power").data.number;
	l->attenuation = json_get(json, "attenuation").data.number;
	l->falloff = (int)json_get(json, "falloff").data.number;
	l->spot_size = (int)json_get(json, "spot_size").data.number;
	l->ambient_coef = (int)json_get(json, "ambient_coef").data.number;
}

void		fill_primitive(t_value v, int i, void *obj)
{
	ENGINE					*engine;
	t_rtprim				*p;
	t_objprim				prim;
	t_json					*j;

	(void)i;
	engine = (ENGINE *)obj;
	prim = get_fct_primitive(key_primitive(djb2(json_get(v.data.obj,
		"type").data.s)));
	if (prim.fct != NULL)
	{
		p = new_rtprim(&engine->scene);
		p->prim = create_primitive(v, prim);
		if (json_get(v.data.obj, "transform").error != TYPE_ERROR)
		{
			j = json_get(v.data.obj, "transform").data.obj;
			p->transform = new_rttransform(&engine->scene,
					get_vec3_json(json_get(j, "position")),
				vec3_normalize(get_vec3_json(json_get(j, "rotation"))),
					get_vec3_json(json_get(j, "scaling")));
		}
		p->material = get_mtl_by_name(&engine->scene,
			json_get(v.data.obj, "material").data.s);
	}
}
