/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 12:56:12 by mbarbari          #+#    #+#             */
/*   Updated: 2017/02/10 12:56:25 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	check_mouse(t_framework *f, SDL_Event e)
{
	Uint8		type;
	t_point2	mousepos;
	t_callback	c;

	mousepos = get_mouse_pos(f);
	c = f->mousemove[e.button.windowID];
	if (mousemoved(f) && c.function)
		c.function(f->mousemove[e.button.windowID].arg, mousepos);
	f->lastmousepos = mousepos;
	if (e.type == SDL_MOUSEBUTTONDOWN
	|| e.type == SDL_MOUSEBUTTONUP)
	{
		type = e.type == SDL_MOUSEBUTTONDOWN;
		c = f->mouse[e.button.windowID][e.button.button][type];
		f->buttons[e.button.button] = type;
		if (c.function)
			c.function(c.arg, e.button.button);
	}
}

void	check_keyboard(t_framework *f, SDL_Event e)
{
	t_callback	c;

	if (e.type == SDL_KEYDOWN)
	{
		c = f->keydown[e.key.windowID][e.key.keysym.scancode][e.key.repeat];
		f->keys[e.key.keysym.scancode] = 1;
		if (c.function)
			c.function(c.arg, e.key.keysym.scancode);
	}
	else if (e.type == SDL_KEYUP)
	{
		c = f->keyup[e.key.windowID][e.key.keysym.scancode];
		f->keys[e.key.keysym.scancode] = 0;
		if (c.function)
			c.function(c.arg, e.key.keysym.scancode);
	}
}
