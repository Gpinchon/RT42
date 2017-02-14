/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/03 20:57:30 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/13 11:36:13 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*clear_window(void *window)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!window, NULL_OBJECT_POINTER, "clear_window");
	win = get_data_pointer(window, sizeof(t_window));
	FRAMEWORK_DEBUG(!win, NULL_WINDOW_POINTER, "clear_window");
	SDL_FillRect(win->sdl_surface, NULL,
		map_color(win->sdl_surface, &win->clear_color));
	return (window);
}

void	*clear_window_image(void *window)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!window, NULL_OBJECT_POINTER, "clear_window");
	win = get_data_pointer(window, sizeof(t_window));
	FRAMEWORK_DEBUG(!win, NULL_WINDOW_POINTER, "clear_window");
	if (win->attached_image)
		fill_image(win->attached_image, &win->clear_color);
	return (window);
}

void	*fill_window(void *window, void *color)
{
	t_window	*wstruc;

	FRAMEWORK_DEBUG(!window, NULL_OBJECT_POINTER, "clear_window");
	wstruc = get_data_pointer(window, sizeof(t_window));
	FRAMEWORK_DEBUG(!wstruc, NULL_WINDOW_POINTER, "clear_window");
	SDL_FillRect(wstruc->sdl_surface, NULL,
		map_color(wstruc->sdl_surface, color));
	return (window);
}

void	*refresh_window(void *window)
{
	t_window	*wstruct;

	FRAMEWORK_DEBUG(!window, NULL_OBJECT_POINTER, "refresh_window");
	wstruct = get_data_pointer(window, sizeof(t_window));
	FRAMEWORK_DEBUG(!wstruct, NULL_WINDOW_POINTER, "refresh_window");
	if (wstruct->attached_image)
		put_image_stretched(window, wstruct->attached_image);
	SDL_UpdateWindowSurface(wstruct->sdl_window);
	if (wstruct->gl_context)
		SDL_GL_SwapWindow(wstruct->sdl_window);
	return (window);
}
