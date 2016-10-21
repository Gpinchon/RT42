/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 17:07:53 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/07 14:43:09 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>
#include <stdio.h>


void	*attach_image_to_window(void *window, void *image)
{
	t_window	*win;
	t_img		*img;

	win = get_data_pointer(window, sizeof(t_window));
	FRAMEWORK_DEBUG(!image, NULL_IMAGE_POINTER, "attach_image_to_window");
	win->attached_image = image;
	img = get_data_pointer(win->attached_image, sizeof(t_img));
	img->sdl_surface = SDL_ConvertSurface(img->sdl_surface,
		win->sdl_surface->format, 0);
	return (image);
}

void	*get_attached_image(void *window)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!window, NULL_IMAGE_POINTER, "get_attached_image");
	win = get_data_pointer(window, sizeof(t_window));
	return (win->attached_image);
}
