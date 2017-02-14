/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/02 15:31:54 by gpinchon          #+#    #+#             */
/*   Updated: 2017/02/10 12:51:03 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sdl_framework.h>
#include <stdio.h>
#include <pthread.h>

void	press(void *image)
{
	t_rgba	color;
	int		w;
	int		h;

	color = rgba(255, 255, 0, 255);
	get_image_size(image, &w, &h);
	put_image_pixel(image, &color, (t_point2){rand() / (float)RAND_MAX * w,
			rand() / (float)RAND_MAX * h});
}

void	repeat(void *image)
{
	t_rgba	color;
	int		w;
	int		h;
	int		i;

	w = 0;
	h = 0;
	i = 0;
	get_image_size(image, &w, &h);
	while (i < w)
	{
		color = rgba(rand() / (float)RAND_MAX * 255,
				rand() / (float)RAND_MAX * 255,
				rand() / (float)RAND_MAX * 255,
				rand() / (float)RAND_MAX * 255);
		put_image_pixel(image, &color, (t_point2){rand() / (float)RAND_MAX * i,
				rand() / (float)RAND_MAX * h});
		i++;
	}
}

void	refresh(void *window)
{
	refresh_window(window);
}

void	mousemove(void *window, t_point2 mousepos)
{
	t_rgba	color;

	color = rgba(rand() / (float)RAND_MAX * 255,
			rand() / (float)RAND_MAX * 255,
			rand() / (float)RAND_MAX * 255, rand() / (float)RAND_MAX * 255);
	put_window_image_pixel(window, &color, mousepos);
}

int		main(int argc, char **argv)
{
	void	*framework;
	void	*winwin;
	void	*image;

	framework = new_framework();
	winwin = new_window(framework, 768, 768, "test");
	image = load_image_file(framework, "./Graphics_duck.bmp");
	attach_image_to_window(winwin, image);
	set_loop_hook(framework, new_callback(refresh, winwin));
	set_keypress_hook(framework, winwin, "Escape",
			new_callback(exit_framework, framework));
	set_mousemove_hook(framework, winwin, new_callback(mousemove, winwin));
	set_keypress_hook(framework, winwin, "Space", new_callback(press, image));
	set_keyrepeat_hook(framework, winwin, "Space", new_callback(repeat, image));
	set_onexit_hook(framework, new_callback(destroy_framework, framework));
	framework_loop(framework);
	return (argc + argv[0][0]);
}
