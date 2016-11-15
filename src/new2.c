/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:04:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 20:48:24 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*new_material(SCENE *scene)
{
	LINK		*new_link;

	if (!scene->material)
		new_link = scene->material = new_ezlink(other, 1, sizeof(MATERIAL));
	else
	{
		new_link = new_ezlink(other, 1, sizeof(MATERIAL));
		ezlink_append(scene->material, new_link);
	}
	return (new_link->data.data);
}

RTPRIMITIVE	*new_rtprim(SCENE *scene)
{
	RTPRIMITIVE	primitive;

	memset(&primitive, 0, sizeof(RTPRIMITIVE));
	if (!scene->primitive.length)
		scene->primitive = new_ezarray(other, scene->primitive.length + 1, sizeof(RTPRIMITIVE));
	else
		ezarray_push(&scene->primitive, &primitive);
	return (ezarray_get_index(scene->primitive, scene->primitive.length - 1));
}

CAMERA		*new_camera(SCENE *scene)
{
	CAMERA	camera;

	memset(&camera, 0, sizeof(CAMERA));
	if (!scene->camera.length)
		scene->camera = new_ezarray(other, scene->camera.length + 1, sizeof(CAMERA));
	else
		ezarray_push(&scene->camera, &camera);
	return (ezarray_get_index(scene->camera, scene->camera.length - 1));
}

TRANSFORM	*new_transform(SCENE *scene, VEC3 position, VEC3 rotation, VEC3 scale)
{
	LINK		*new_link;

	if (!scene->transform)
		new_link = scene->transform = new_ezlink(other, 1, sizeof(TRANSFORM));
	else
	{
		new_link = new_ezlink(other, 1, sizeof(TRANSFORM));
		ezlink_append(scene->transform, new_link);
	}
	((TRANSFORM*)scene->transform->data.data)->position = position;
	((TRANSFORM*)scene->transform->data.data)->rotation = rotation;
	((TRANSFORM*)scene->transform->data.data)->scale = scale;
	return (new_link->data.data);
}
