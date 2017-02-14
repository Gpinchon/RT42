/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 15:51:53 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/07 01:32:40 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*fill_image(void *image, void *color)
{
	SDL_Surface	*s;
	t_img		*istruct;

	FRAMEWORK_DEBUG(!image, NULL_OBJECT_POINTER, "fill_image");
	istruct = ((GSTRUCT*)image)->data;
	FRAMEWORK_DEBUG(!istruct, NULL_IMAGE_POINTER, "fill_image");
	s = istruct->sdl_surface;
	SDL_FillRect(s, NULL, map_color(s, color));
	return (image);
}
