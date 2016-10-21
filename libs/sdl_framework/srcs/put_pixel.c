/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 17:48:07 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/07 17:16:32 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*put_image_pixel(void *image, void *color, t_point2 position)
{
	void	*p;
	t_img	*img;
	Uint32	sdl_col;

	img = get_data_pointer(image, sizeof(t_img));
	sdl_col = map_color(img->sdl_surface, color);
	p = get_image_pixel(image, position);
	SDL_LockSurface(img->sdl_surface);
	*(Uint32 *)p = sdl_col;
	SDL_UnlockSurface(img->sdl_surface);
	return (p);
}


void	*put_window_pixel(void *window, void *color, t_point2 position)
{
	void		*p;
	t_window	*win;
	Uint32		sdl_col;

	win = get_data_pointer(window, sizeof(t_window));
	sdl_col = map_color(win->sdl_surface, color);
	p = get_window_pixel(window, position);
	SDL_LockSurface(win->sdl_surface);
	*(Uint32 *)p = sdl_col;
	SDL_UnlockSurface(win->sdl_surface);
	return (p);
}
