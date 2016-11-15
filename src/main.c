/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:32:51 by gpinchon          #+#    #+#             */
/*   Updated: 2016/11/15 10:45:23 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		assign_color_bits(void *pixel)
{
	*((UCHAR*)pixel) = 200;
}

void		blit_buffer(FRAMEBUFFER buffer, void *image)
{
	UINT 	i;
	IMGDATA	img;

	i = 0;
	img = get_image_data(image);
	if (img.size.x == buffer.size.x
	&& img.size.y == buffer.size.y
	&& img.bpp == buffer.bpp)
		while (i < buffer.array.length)
		{
			((UCHAR*)img.pixels)[i] = *((UCHAR*)ezarray_get_index(buffer.array, i));
			i++;
		}
}

void		destroy_engine(ENGINE *engine)
{
	destroy_ezarray(&engine->framebuffer.array);
	destroy_ezarray(&engine->depthbuffer.array);
	destroy_ezarray(&engine->normalbuffer.array);
	destroy_ezarray(&engine->mtlbuffer.array);
}

int main(void)
{
	ENGINE	engine;

	engine = new_engine();
	ezforeach(engine.framebuffer.array, assign_color_bits);
	blit_buffer(engine.framebuffer, engine.image);
	refresh_window(engine.window);
	framework_loop(engine.framework);
	destroy_engine(&engine);
	return (0);
}
