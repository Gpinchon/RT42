/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:59:58 by gpinchon          #+#    #+#             */
/*   Updated: 2016/07/06 21:37:21 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

void	framework_loop(void *framework)
{
	SDL_Event	e;
	t_framework	*f;
	Uint32		i[3];

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "framework_loop");
	f = framework;
	while (!f->done)
	{
		SDL_PollEvent(&e);
		i[0] = e.key.windowID;
		i[1] = e.key.keysym.scancode;
		i[2] = e.key.repeat;
		if (e.type == SDL_QUIT)
			break ;
		if (f->loop.function)
			f->loop.function(f->loop.arg);
		if (e.type == SDL_MOUSEMOTION
			&& f->mousemove[i[0]].function)
			f->mousemove[i[0]].
			function(f->mousemove[i[0]].arg, get_mouse_pos(framework));
		if (e.type == SDL_MOUSEBUTTONDOWN
			&& f->mousedown[i[0]][e.key.button].function)
			f->mousedown[i[0]][e.key.button].
			function(f->mousedown[i[0]][e.key.button].arg, e.key.button)
		else if (e.type == SDL_MOUSEBUTTONUP
			&& f->mouseup[i[0]][e.key.button].function)
			f->mouseup[i[0]][e.key.button].
			function(f->mouseup[i[0]][e.key.button].arg, e.key.button)
		if (e.type == SDL_KEYDOWN
			&& f->keydown[i[0]][i[1]][i[2]].function)
		{
			f->keydown[i[0]][i[1]][i[2]].
			function(f->keydown[i[0]][i[1]][i[2]].arg, i[1]);
			f->keys[i[1]] = 1;
		}
		else if (e.type == SDL_KEYUP
			&& f->keyup[i[0]][i[1]].function)
		{
			f->keyup[i[0]][i[1]].
			function(f->keyup[i[0]][i[1]].arg, i[1]);
			f->keys[i[1]] = 0;
		}
		SDL_Delay(0);
	}
	destroy_framework(f);
}
