/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_progress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:03:14 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/24 14:24:28 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	print_progress(ENGINE *engine, float progress)
{
	t_rgba		color;
	t_point2	coord;
	int			i;
	int			heigth;
	void		*img;

	if ((engine->stop_rendering = framework_is_done(engine->framework)))
		return ;
	color = rgba(127, 255, 212, 255);
	get_image_size(img = engine->loading_screen, &coord.x, &coord.y);
	heigth = (0.05f * coord.y);
	coord = (t_point2){coord.x * progress, coord.y / 2};
	i = coord.y - heigth;
	coord.y += heigth;
	while (i++ < coord.y)
		put_image_pixel(img, &color,
			(t_point2){coord.x, i});
	if (SDL_GetTicks() - engine->last_time >= 150)
	{
		clear_window(engine->window);
		put_image_stretched(engine->window, img);
		engine->last_time = SDL_GetTicks();
		framework_loop_once(engine->framework);
	}
}
