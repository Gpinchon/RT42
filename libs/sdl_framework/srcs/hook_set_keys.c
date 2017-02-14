/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_set_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 19:14:24 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/20 12:56:02 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	set_keyup_hook(void *framework, void *window,
	char *keyname, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_keyup_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->keyup[win->id]
	[SDL_GetScancodeFromName(keyname)] = callback;
}

void	set_keypress_hook(void *framework, void *window,
	char *keyname, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_keypress_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->keydown[win->id]
	[SDL_GetScancodeFromName(keyname)][0] = callback;
}

void	set_keyrepeat_hook(void *framework, void *window,
	char *keyname, t_callback callback)
{
	t_window	*win;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "set_keyrepeat_hook");
	win = get_data_pointer(window, sizeof(t_window));
	((t_framework*)framework)->keydown[win->id]
	[SDL_GetScancodeFromName(keyname)][1] = callback;
}
