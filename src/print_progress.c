/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_progress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:03:14 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/23 15:03:50 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	print_progress(ENGINE *engine, float progress)
{
	t_rgba		color;
	t_point2	img_size;
	int			i;
	int			heigth;

	if ((engine->stop_rendering = framework_is_done(engine->framework)))
		return ;
	color = rgba(255, 0, 0, 255);
	get_image_size(engine->loading_screen, &img_size.x, &img_size.y);
	heigth = (5.f / 100.f * img_size.y);
	i = img_size.y / 2 - heigth;
	while (i < (img_size.y / 2) + heigth)
	{
		put_image_pixel(engine->loading_screen, &color,
			(t_point2){img_size.x * progress / 100.f, i});
		i++;
	}
	if (SDL_GetTicks() - engine->last_time >= 100)
	{
		clear_window(engine->window);
		put_image_stretched(engine->window, engine->loading_screen);
		engine->last_time = SDL_GetTicks();
		framework_loop_once(engine->framework);
	}
}
