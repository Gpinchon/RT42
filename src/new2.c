/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:04:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/30 22:19:35 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

RTPRIMITIVE	*new_rtprim(SCENE *scene)
{
	RTPRIMITIVE	primitive;

	vml_memset(&primitive, 0, sizeof(RTPRIMITIVE));
	if (!scene->primitives.length)
		scene->primitives = new_ezarray(other, scene->primitives.length + 1, sizeof(RTPRIMITIVE));
	else
		ezarray_push(&scene->primitives, &primitive);
	return (ezarray_get_index(scene->primitives, scene->primitives.length - 1));
}

MATERIAL	*new_material(SCENE *scene, char *name)
{
	LINK		*new_link;
	MATERIAL	*mtl;

	if ((mtl = get_mtl_by_name(scene, name)))
		return (mtl);
	if (!scene->materials)
		new_link = scene->materials = new_ezlink(other, 1, sizeof(MATERIAL));
	else
	{
		new_link = new_ezlink(other, 1, sizeof(MATERIAL));
		ezlink_append(scene->materials, new_link);
	}
	((MATERIAL*)ezlink_get_data(new_link))->name = strcpy(malloc(sizeof(char) * strlen(name)), name);
	((MATERIAL*)ezlink_get_data(new_link))->uv_scale = (VEC2){1, 1};
	((MATERIAL*)ezlink_get_data(new_link))->refraction = 1.f;
	((MATERIAL*)ezlink_get_data(new_link))->alpha = 1;
	((MATERIAL*)ezlink_get_data(new_link))->parallax = 0.05;
	return (ezlink_get_data(new_link));
}

CAMERA		*new_camera(SCENE *scene, float fov, float znear, float zfar)
{
	LINK	*new_link;

	if (!scene->cameras)
		new_link = scene->cameras = new_ezlink(other, 1, sizeof(CAMERA));
	else
	{
		new_link = new_ezlink(other, 1, sizeof(CAMERA));
		ezlink_append(scene->cameras, new_link);
	}
	((CAMERA*)ezlink_get_data(new_link))->fov = 180 - fov;
	((CAMERA*)ezlink_get_data(new_link))->znear = znear;
	((CAMERA*)ezlink_get_data(new_link))->zfar = zfar;
	return (ezlink_get_data(new_link));
}

TRANSFORM	*new_transform(SCENE *scene, VEC3 position, VEC3 rotation, VEC3 scaling)
{
	LINK		*new_link;

	new_link = new_ezlink(other, 1, sizeof(TRANSFORM));
	if (!scene->transforms)
		scene->transforms = new_link;
	else
		ezlink_append(scene->transforms, new_link);
	((TRANSFORM*)ezlink_get_data(new_link))->position = position;
	((TRANSFORM*)ezlink_get_data(new_link))->rotation = rotation;
	((TRANSFORM*)ezlink_get_data(new_link))->scaling = scaling;
	return (ezlink_get_data(new_link));
}

LIGHT		*new_light(SCENE *scene, UCHAR type, VEC3 position)
{
	LIGHT	new_light;
	LIGHT	*lptr;

	vml_memset(&new_light, 0, sizeof(LIGHT));
	new_light.type = type;
	new_light.position = position;
	new_light.color = (VEC3){1, 1, 1};
	new_light.power = 1.f;
	if (!scene->lights.length)
	{
		scene->lights = new_ezarray(other, 1, sizeof(LIGHT));
		lptr = ezarray_get_index(scene->lights, 0);
		*lptr = new_light;
	}
	else
		ezarray_push(&scene->lights, &new_light);
	return (ezarray_get_index(scene->lights, scene->lights.length - 1));
}
