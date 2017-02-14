/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 14:17:20 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 12:47:16 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

static void	*add_window(t_framework *framework, GSTRUCT *window)
{
	if (!framework->windows)
		return (framework->windows = window);
	else
		return (append_object((void*)window, (void*)framework->windows));
}

void		*new_window(void *framework,
	int width, int height, char *name)
{
	t_generic	*gstruct;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "new_window");
	FRAMEWORK_DEBUG((width <= 0 || height <= 0),
		INVALID_WINDOW_SIZE, "new_window");
	gstruct = new_object(sizeof(t_window));
	((t_window*)gstruct->data)->sdl_window = SDL_CreateWindow(name,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	FRAMEWORK_DEBUG(!((t_window*)gstruct->data)->sdl_window,
		SDL_ERROR, "new_window");
	((t_window*)gstruct->data)->sdl_surface =
	SDL_GetWindowSurface(((t_window*)gstruct->data)->sdl_window);
	((t_window*)gstruct->data)->id =
	SDL_GetWindowID(((t_window*)gstruct->data)->sdl_window);
	((t_window*)gstruct->data)->clear_color = CLEAR_COLOR;
	((t_window*)gstruct->data)->gl_context = NULL;
	((t_window*)gstruct->data)->clear_bits = GL_COLOR_BUFFER_BIT;
	add_window(framework, gstruct);
	clear_window(gstruct);
	return (refresh_window(gstruct));
}

void		*new_gl_context(void *w)
{
	if (!((t_window*)((GSTRUCT*)w)->data)->gl_context)
		return (((t_window*)((GSTRUCT*)w)->data)->gl_context =
		SDL_GL_CreateContext(((t_window*)((GSTRUCT*)w)->data)->sdl_window));
		return (NULL);
}

void		set_window_clear_bits(void *window, GLbitfield clear_bits)
{
	t_window *win;

	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "set_window_clear_bits");
	win = get_data_pointer(window, sizeof(t_window));
	win->clear_bits = clear_bits;
}
