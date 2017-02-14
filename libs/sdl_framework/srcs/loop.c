/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:59:58 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 12:54:54 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal_framework.h>

Uint8	mousemoved(void *framework)
{
	t_point2	mousepos;
	t_point2	lastmousepos;

	mousepos = get_mouse_pos(framework);
	lastmousepos = ((t_framework*)framework)->lastmousepos;
	return (lastmousepos.x != mousepos.x || lastmousepos.y != mousepos.y);
}

char	framework_is_done(void *framework)
{
	return (((t_framework*)framework)->done);
}

void	framework_loop_once(void *framework)
{
	t_framework	*f;
	SDL_Event	e;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "framework_loop_once");
	f = framework;
	if (f->done)
		return ;
	if (f->loop.function)
		f->loop.function(f->loop.arg);
	if (!SDL_PollEvent(&e)
	|| (f->done = e.type == SDL_QUIT))
		return ;
	else if (e.type == SDL_APP_LOWMEMORY && f->low_mem.function)
		f->low_mem.function(f->low_mem.arg);
	else
	{
		check_mouse(framework, e);
		check_keyboard(framework, e);
	}
}

void	framework_loop(void *framework)
{
	SDL_Event	e;
	t_framework	*f;
	t_callback	loop;

	FRAMEWORK_DEBUG(!framework, NULL_FRAMEWORK_POINTER, "framework_loop");
	f = framework;
	while (!f->done)
	{
		loop = f->loop;
		if (loop.function)
			loop.function(loop.arg);
		if (SDL_PollEvent(&e))
		{
			if ((f->done = e.type == SDL_QUIT))
			{
				if (f->onexit.function)
					f->onexit.function(f->onexit.arg);
				break ;
			}
			if (e.type == SDL_APP_LOWMEMORY && f->low_mem.function)
				f->low_mem.function(f->low_mem.arg);
			check_mouse(framework, e);
			check_keyboard(framework, e);
		}
	}
}
