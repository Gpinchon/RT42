/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:01:41 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/07 17:08:38 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*put_image(void *window, void *image, t_point2 position)
{
	t_window	*wstruct;
	t_img		*istruct;
	SDL_Rect	dst;

	FRAMEWORK_DEBUG(!image, NULL_IMAGE_POINTER, "put_image");
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "put_image");
	wstruct = get_data_pointer(window, sizeof(t_window));
	istruct = get_data_pointer(image, sizeof(t_img));
	dst.x = position.x;
	dst.y = position.y;
	dst.w = position.x + istruct->sdl_surface->w;
	dst.h = position.y + istruct->sdl_surface->h;
	SDL_BlitSurface(istruct->sdl_surface, NULL, wstruct->sdl_surface, &dst);
	return (image);
}

void	*put_image_stretched(void *window, void *image)
{
	t_window	*wstruct;
	t_img		*istruct;
	SDL_Rect	dst;

	FRAMEWORK_DEBUG(!image, NULL_IMAGE_POINTER, "put_image");
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "put_image");
	wstruct = get_data_pointer(window, sizeof(t_window));
	istruct = get_data_pointer(image, sizeof(t_img));
	dst.x = 0;
	dst.y = 0;
	dst.w = wstruct->sdl_surface->w;
	dst.h = wstruct->sdl_surface->h;
	SDL_BlitScaled(istruct->sdl_surface, NULL, wstruct->sdl_surface, &dst);
	return (image);
}
