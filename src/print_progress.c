/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_progress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:03:14 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/15 18:08:34 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline void	display_loading(ENGINE *engine, void *img)
{
	clear_window(engine->window);
	put_image_stretched(engine->window, img);
	engine->last_time = SDL_GetTicks();
	framework_loop_once(engine->framework);
}

void				print_progress(ENGINE *engine, float progress)
{
	t_rgba		color;
	t_point2	c;
	t_point2	i;
	t_point2	size;
	void		*img;

	if ((engine->stop_rendering = framework_is_done(engine->framework)))
		return ;
	color = rgba(127, 255, 212, 255);
	get_image_size(img = engine->loading_screen, &c.x, &c.y);
	size = (t_point2){0.08f * c.x, 0.05f * c.y};
	c = (t_point2){c.x * progress, c.y / 2};
	i = (t_point2){c.x - size.x, c.y - size.y};
	i.x = i.x > 0 ? i.x : 0;
	c = (t_point2){CLAMP(c.x + size.x, 0, c.x / progress), c.y += size.y};
	while (++i.y < c.y)
	{
		i.x = c.x - size.x;
		while (++i.x < c.x)
			put_image_pixel(img, &color,
				(t_point2){i.x, i.y});
	}
	display_loading(engine, img);
}
