/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/03 22:59:09 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/06 22:13:49 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

t_rgb	rgb(Uint8 r, Uint8 g, Uint8 b)
{
	return ((t_rgb){RGBCOL, r, g, b});
}

t_rgba	rgba(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return ((t_rgba){RGBACOL, r, g, b, a});
}

Uint32	map_color(SDL_Surface *surface, void *color)
{
	FRAMEWORK_DEBUG(!surface, NULL_SURFACE_POINTER, "map_color");
	FRAMEWORK_DEBUG(!color, NULL_COLOR_POINTER, "map_color");
	FRAMEWORK_DEBUG(
		((t_rgb*)color)->type != RGBCOL &&
		((t_rgb*)color)->type != RGBACOL, UNKNOW_COLOR_TYPE, "map_color");
	return (((t_rgb*)color)->type == RGBCOL ?
		SDL_MapRGB(surface->format,
			((t_rgb*)color)->r,
			((t_rgb*)color)->g,
			((t_rgb*)color)->b) :
		SDL_MapRGBA(surface->format,
			((t_rgba*)color)->r,
			((t_rgba*)color)->g,
			((t_rgba*)color)->b,
			((t_rgba*)color)->a));
}
