/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:04:09 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/11 22:12:35 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

RTPRIMITIVE	*new_rtprim(SCENE *s)
{
	RTPRIMITIVE	primitive;

	vml_memset(&primitive, 0, sizeof(RTPRIMITIVE));
	if (!s->primitives.length)
		s->primitives = new_ezarray(other, s->primitives.length + 1,
			sizeof(RTPRIMITIVE));
	else
		ezarray_push(&s->primitives, &primitive);
	return (ezarray_get_index(s->primitives, s->primitives.length - 1));
}

CAMERA		*new_camera(SCENE *scene, float fov, float znear, float zfar)
{
	t_ezlink	*new_link;

	if (!scene->cameras)
	{
		new_link = new_ezlink(other, 1, sizeof(CAMERA));
		scene->cameras = new_link;
	}
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

RTTRANSFORM	*new_rttransform(SCENE *scene, VEC3 p,
	VEC3 r, VEC3 s)
{
	t_ezlink		*nl;

	nl = new_ezlink(other, 1, sizeof(RTTRANSFORM));
	if (!scene->transforms)
		scene->transforms = nl;
	else
		ezlink_append(scene->transforms, nl);
	((RTTRANSFORM*)ezlink_get_data(nl))->current =
	new_transform(p, r, s, UPVEC);
	return (ezlink_get_data(nl));
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
