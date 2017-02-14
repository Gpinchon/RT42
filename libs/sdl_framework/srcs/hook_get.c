/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 12:50:04 by gpinchon          #+#    #+#             */
/*   Updated: 2016/12/20 12:56:31 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

Uint8		get_key_status(void *framework, Uint32 keycode)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "get_key_status");
	FRAMEWORK_DEBUG(keycode > MAX_SCAN, INVALID_KEYCODE, "get_key_status");
	return (((t_framework*)framework)->keys[keycode]);
}

Uint8		get_button_status(void *framework, Uint8 button)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "get_button_status");
	FRAMEWORK_DEBUG(button > MAX_BUTTON, INVALID_KEYCODE, "get_button_status");
	return (((t_framework*)framework)->buttons[button]);
}

t_point2	get_mouse_pos(void *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "get_mouse_pos");
	SDL_GetMouseState(&((t_framework*)framework)->mousepos.x,
		&((t_framework*)framework)->mousepos.y);
	return (((t_framework*)framework)->mousepos);
}

t_point2	get_last_mouse_pos(void *framework)
{
	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "get_last_mouse_pos");
	return (((t_framework*)framework)->lastmousepos);
}
