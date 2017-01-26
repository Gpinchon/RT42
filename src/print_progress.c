/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_progress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:03:14 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/25 23:28:32 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static inline void	display_loading(ENGINE *engine, void *img)
{
	if (SDL_GetTicks() - engine->last_time >= 100)
	{
		clear_window(engine->window);
		put_image_stretched(engine->window, img);
		engine->last_time = SDL_GetTicks();
		framework_loop_once(engine->framework);
	}
}

void	print_progress(ENGINE *engine, float progress)
{
	t_rgba		color;
	t_point2	coord;
	t_point2	i;
	t_point2	size;
	void		*img;

	if ((engine->stop_rendering = framework_is_done(engine->framework)))
		return ;
	color = rgba(127, 255, 212, 255);
	get_image_size(img = engine->loading_screen, &coord.x, &coord.y);
	size = (t_point2){0.08f * coord.x, 0.05f * coord.y};
	coord = (t_point2){coord.x * progress, coord.y / 2};
	i = (t_point2){coord.x - size.x, coord.y - size.y};
	i.x = i.x > 0 ? i.x : 0;
	coord = (t_point2){coord.x += size.x, coord.y += size.y};
	coord.x = coord.x < coord.x / progress ? coord.x : coord.x / progress;
	while (i.y++ < coord.y)
	{
		i.x = coord.x - size.x;
		while (i.x++ < coord.x)
			put_image_pixel(img, &color,
				(t_point2){i.x, i.y});
	}
	display_loading(engine, img);
}
