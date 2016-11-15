/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:44:45 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 10:47:40 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

FRAMEBUFFER	new_framebuffer(TYPE type, t_point2 size, Uint8 depth)
{
	FRAMEBUFFER	buffer;

	buffer.array = new_ezarray(type, size.x * size.y * depth);
	buffer.size = size;
	buffer.bpp = depth * buffer.array.data_size * 8;
	buffer.sizeline = size.y * depth;
	return (buffer);
}

SCENE		new_scene()
{
	SCENE	scene;

	memset(&scene, 0, sizeof(SCENE));
	return (scene);
}

TRANSFORM	new_transform(VEC3 position, VEC3 rotation, VEC3 scale)
{
	TRANSFORM	transform;

	memset(&transform, 0, sizeof(TRANSFORM));
	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;
	return (transform);
}

ENGINE		new_engine()
{
	ENGINE	engine;

	memset(&engine, 0, sizeof(ENGINE));
	engine.framework = new_framework();
	engine.window = new_window(engine.framework, WINDOW_SIZE.x, WINDOW_SIZE.y, "RT");
	engine.image = new_image(engine.framework, BUFFER_SIZE.x, BUFFER_SIZE.y);
	engine.framebuffer = new_framebuffer(unsigned_char, BUFFER_SIZE, 4);
	engine.depthbuffer = new_framebuffer(FLOAT, BUFFER_SIZE, 1);
	engine.normalbuffer = new_framebuffer(FLOAT, BUFFER_SIZE, 3);
	engine.mtlbuffer = new_framebuffer(FLOAT, BUFFER_SIZE, sizeof(t_mtl) / sizeof(float));
	attach_image_to_window(engine.window, engine.image);
	return (engine);
}
