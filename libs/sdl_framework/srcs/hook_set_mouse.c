/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_set_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 12:52:40 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/20 12:53:28 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	set_mousemove_hook(void *framework, void *window,
	t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_mousemove_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->mousemove[win->id] = callback;
}

void	set_mousedown_hook(void *framework, void *window,
	Uint8 button, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_mousedown_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->mouse[win->id][button][1] = callback;
}

void	set_mouseup_hook(void *framework, void *window,
	Uint8 button, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_mouseup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->mouse[win->id][button][0] = callback;
}
