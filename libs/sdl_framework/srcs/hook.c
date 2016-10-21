/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 19:14:24 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/06 21:09:04 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

Uint8		get_key_status(void *framework, Uint32 keycode)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "key_status");
	FRAMEWORK_DEBUG(keycode > MAX_SCAN, NULL_FRAMEWORK_POINTER, "key_status");
	return (((t_framework*)framework)->keys[keycode]);
}

t_point2	get_mouse_pos(void *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "key_status");
	SDL_GetMouseState(&((t_framework*)framework)->mousepos.x, &((t_framework*)framework)->mousepos.y);
	return (((t_framework*)framework)->mousepos);
}

void	assign_loop_hook(void *framework, t_callback callback)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_loop_hook");
	((t_framework*)framework)->loop = callback;
}

void	assign_keyup_hook(void *framework, void *window,
	Uint32 keycode, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->keyup[win->id][keycode] = callback;
}

void	assign_keyrepeat_hook(void *framework, void *window,
	Uint32 keycode, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->keydown[win->id][keycode][1] = callback;
}

void	assign_keypress_hook(void *framework, void *window,
	Uint32 keycode, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->keydown[win->id][keycode][0] = callback;
}

void	assign_mousemove_hook(void *framework, void *window,
	t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->mousemove[win->id] = callback;
}

void	assign_mousedown_hook(void *framework, void *window,
	Uint8 button, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->mousedown[win->id][button] = callback;
}

void	assign_mouseup_hook(void *framework, void *window,
	Uint8 button, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "assign_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->mouseup[win->id][button] = callback;
}
