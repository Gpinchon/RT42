/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 17:40:22 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/20 13:02:53 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*get_image_pixel(void *image, t_point2 position)
{
	t_img	*img;

	img = get_data_pointer(image, sizeof(t_img));
	FRAMEWORK_DEBUG(
		position.x >= img->sdl_surface->w || position.x < 0 ||
		position.y >= img->sdl_surface->h || position.y < 0,
		WRONG_IMAGE_COORD, "get_image_pixel");
	return (img->sdl_surface->pixels +
		position.y * img->sdl_surface->pitch +
		position.x * img->sdl_surface->format->BytesPerPixel);
}

void	*get_window_pixel(void *window, t_point2 position)
{
	t_window	*win;

	win = get_data_pointer(window, sizeof(t_window));
	FRAMEWORK_DEBUG(
		position.x >= win->sdl_surface->w || position.x < 0 ||
		position.y >= win->sdl_surface->h || position.y < 0,
		WRONG_IMAGE_COORD, "get_window_pixel");
	return (win->sdl_surface->pixels +
		position.y * win->sdl_surface->pitch +
		position.x * win->sdl_surface->format->BytesPerPixel);
}
