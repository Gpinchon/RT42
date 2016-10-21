/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:45:50 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/06 16:47:20 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	*destroy_window(void *framework, void *window)
{
	GSTRUCT		*win;
	t_window	*winwin;

	win = NULL;
	FRAMEWORK_DEBUG(!window, NULL_WINDOW_POINTER, "destroy_window");
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "destroy_window");
	if (window == ((t_framework*)framework)->windows)
		((t_framework*)framework)->windows = ((GSTRUCT*)window)->next;
	if ((win = (GSTRUCT *)((GSTRUCT*)window)->prev))
	{
		win->next = ((GSTRUCT*)window)->next;
		if (win->next)
			win->next->prev = win;
	}
	else if ((win = (GSTRUCT *)((GSTRUCT*)window)->next))
		win->prev = NULL;
	winwin = get_data_pointer(window, sizeof(t_window));
	SDL_DestroyWindow(winwin->sdl_window);
	free(window);
	return (win);
}

void	destroy_windows(void *f)
{
	GSTRUCT	*win[2];

	FRAMEWORK_DEBUG(!f, NULL_FRAMEWORK_POINTER, "destroy_windows");
	win[0] = ((t_framework*)f)->windows;
	while (win[0])
	{
		win[1] = win[0]->next;
		destroy_window(f, win[0]);
		win[0] = win[1];
	}
}
