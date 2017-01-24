/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_progress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:03:14 by gpinchon          #+#    #+#             */
/*   Updated: 2017/01/24 14:08:49 by gpinchon         ###   ########.fr       */
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
	color = rgba(127, 255, 212, 255);
	get_image_size(engine->loading_screen, &img_size.x, &img_size.y);
	heigth = (0.05f * img_size.y);
	img_size = (t_point2){img_size.x * progress, img_size.y / 2};
	i = img_size.y - heigth;
	img_size.y += heigth;
	while (i < img_size.y)
	{
		put_image_pixel(engine->loading_screen, &color,
			(t_point2){img_size.x, i});
		i++;
	}
	if (SDL_GetTicks() - engine->last_time >= 150)
	{
		clear_window(engine->window);
		put_image_stretched(engine->window, engine->loading_screen);
		engine->last_time = SDL_GetTicks();
		framework_loop_once(engine->framework);
	}
}
