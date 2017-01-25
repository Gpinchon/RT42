/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:01:12 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/25 18:34:46 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	clear_uchar_bits(void *pixel)
{
	*((UCHAR*)pixel) = CCLEAR_VALUE;
}

void	clear_float_bits(void *pixel)
{
	*((float*)pixel) = FCLEAR_VALUE;
}

void	clear_buffers(ENGINE *engine)
{
	ezforeach(engine->framebuffer.array, clear_uchar_bits);
	ezforeach(engine->positionbuffer.array, clear_float_bits);
	ezforeach(engine->normalbuffer.array, clear_float_bits);
	//ezforeach(engine->mtlbuffer.array, clear_float_bits);
}

void	clear_renderer(ENGINE *engine)
{
	clear_buffers(engine);
	clear_window(engine->window);
}
