/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:04:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 11:25:01 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

MATERIAL	*new_material(SCENE scene)
{
	MATERIAL	material;

	memset(&material, 0, sizeof(MATERIAL));
	if (!scene.material.length)
		scene.material = new_ezarray(other, scene.material.length + 1, sizeof(MATERIAL));
	else
		ezarray_push(&scene.material, &material);
	return (ezarray_get_index(scene.material, scene.material.length));
}

RTPRIMITIVE	*new_rtprim(SCENE scene, PRIM_TYPE type)
{
	RTPRIMITIVE	primitive;

	memset(&primitive, 0, sizeof(RTPRIMITIVE));
	primitive.prim.type = type;
	if (!scene.primitive.length)
		scene.primitive = new_ezarray(other, scene.primitive.length + 1, sizeof(RTPRIMITIVE));
	else
		ezarray_push(&scene.primitive, &primitive);
	return (ezarray_get_index(scene.primitive, scene.primitive.length));
}

CAMERA		*new_camera(SCENE scene)
{
	CAMERA	camera;

	memset(&camera, 0, sizeof(CAMERA));
	if (!scene.camera.length)
		scene.camera = new_ezarray(other, scene.camera.length + 1, sizeof(CAMERA));
	else
		ezarray_push(&scene.camera, &camera);
	return (ezarray_get_index(scene.camera, scene.camera.length));
}

TRANSFORM	*new_transform(SCENE scene, VEC3 position, VEC3 rotation, VEC3 scale)
{
	TRANSFORM	transform;

	memset(&transform, 0, sizeof(TRANSFORM));
	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;
	if (!scene.transform.length)
		scene.transform = new_ezarray(other, scene.transform.length + 1, sizeof(TRANSFORM));
	else
		ezarray_push(&scene.transform, &transform);
	return (ezarray_get_index(scene.transform, scene.transform.length));
}
